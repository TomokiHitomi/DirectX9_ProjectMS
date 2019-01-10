//=============================================================================
//
// PMX読み込み処理 [ModelLoaderPMX.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ModelLoaderPMX.h"

#include "BaseFunc.h"

#include	<minwindef.h>
#include	<sys/stat.h>	// ファイルサイズ測定用

//#define FILE_PATH "Lat_Pastry.pmx"
#define FILE_PATH "v_flower.pmx"


#define SINTABLE_DIV						(65536)				// サインテーブルの精度

#define PMX_MAX_IKLINKNUM		(64)			// 対応するIKリンクの最大数

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif


struct PMX_BASEINFO
{
	BYTE	EncodeType;						// 文字コードのエンコードタイプ 0:UTF16 1:UTF8
	BYTE	UVNum;							// 追加ＵＶ数 ( 0～4 )
	BYTE	VertexIndexSize;				// 頂点Indexサイズ ( 1 or 2 or 4 )
	BYTE	TextureIndexSize;				// テクスチャIndexサイズ ( 1 or 2 or 4 )
	BYTE	MaterialIndexSize;				// マテリアルIndexサイズ ( 1 or 2 or 4 )
	BYTE	BoneIndexSize;					// ボーンIndexサイズ ( 1 or 2 or 4 )
	BYTE	MorphIndexSize;					// モーフIndexサイズ ( 1 or 2 or 4 )
	BYTE	RigidIndexSize;					// 剛体Indexサイズ ( 1 or 2 or 4 )
};
struct PMX_TXTBUF
{
	int		TxtSize;
	BYTE	*Txt;
};

// 頂点データ
struct PMX_VERTEX
{
	float	Position[3];					// 座標
	float	Normal[3];						// 法線
	float	UV[2];							// 標準UV値
	float	AddUV[4][4];					// 追加UV値
	BYTE	WeightType;						// ウエイトタイプ( 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF )
	int		BoneIndex[4];					// ボーンインデックス
	float	BoneWeight[4];					// ボーンウェイト
	float	SDEF_C[3];						// SDEF-C
	float	SDEF_R0[3];						// SDEF-R0
	float	SDEF_R1[3];						// SDEF-R1
	float	ToonEdgeScale;					// トゥーンエッジのスケール
};

// 面リスト
struct PMX_FACE
{
	int		VertexIndex[3];
};

// テクスチャ情報
struct PMX_TEXTURE
{
	wchar_t	TexturePath[512];
};

// マテリアル情報
struct PMX_MATERIAL
{
	wchar_t	Name[128];						// 名前

	float	Diffuse[4];						// ディフューズカラー
	float	Specular[3];						// スペキュラカラー
	float	SpecularPower;						// スペキュラ定数
	float	Ambient[3];						// アンビエントカラー

	BYTE	CullingOff;						// 両面描画
	BYTE	GroundShadow;						// 地面影
	BYTE	SelfShadowMap;						// セルフシャドウマップへの描画
	BYTE	SelfShadowDraw;					// セルフシャドウの描画
	BYTE	EdgeDraw;							// エッジの描画

	float	EdgeColor[4];					// エッジカラー
	float	EdgeSize;							// エッジサイズ

	int		TextureIndex;						// 通常テクスチャインデックス
	int		SphereTextureIndex;				// スフィアテクスチャインデックス
	BYTE	SphereMode;						// スフィアモード( 0:無効 1:乗算 2:加算 3:サブテクスチャ(追加UV1のx,yをUV参照して通常テクスチャ描画を行う)

	BYTE	ToonFlag;							// 共有トゥーンフラグ( 0:個別Toon 1:共有Toon )
	int		ToonTextureIndex;					// トゥーンテクスチャインデックス

	int		MaterialFaceNum;					// マテリアルが適応されている面の数
};

// ＩＫリンク情報
struct PMX_IKLINK
{
	int		BoneIndex;							// リンクボーンのインデックス
	BYTE	RotLockFlag;						// 回転制限( 0:OFF 1:ON )
	float	RotLockMin[3];					// 回転制限、下限
	float	RotLockMax[3];					// 回転制限、上限
};

// ＩＫ情報
struct PMX_IK
{
	int		TargetBoneIndex;					// IKターゲットのボーンインデックス
	int		LoopNum;							// IK計算のループ回数
	float	RotLimit;							// 計算一回辺りの制限角度

	int		LinkNum;							// ＩＫリンクの数
	PMX_IKLINK Link[PMX_MAX_IKLINKNUM];		// ＩＫリンク情報
};

// ボーン情報
struct PMX_BONE
{
	wchar_t	Name[128];						// 名前
	float	Position[3];						// 座標
	int		ParentBoneIndex;					// 親ボーンインデックス
	int		TransformLayer;					// 変形階層

	BYTE	Flag_LinkDest;						// 接続先
	BYTE	Flag_EnableRot;					// 回転ができるか
	BYTE	Flag_EnableMov;					// 移動ができるか
	BYTE	Flag_Disp;							// 表示
	BYTE	Flag_EnableControl;				// 操作ができるか
	BYTE	Flag_IK;							// IK
	BYTE	Flag_AddRot;						// 回転付与
	BYTE	Flag_AddMov;						// 移動付与
	BYTE	Flag_LockAxis;						// 軸固定
	BYTE	Flag_LocalAxis;					// ローカル軸
	BYTE	Flag_AfterPhysicsTransform;		// 物理後変形
	BYTE	Flag_OutParentTransform;			// 外部親変形

	float	OffsetPosition[3];				// オフセット座標
	int		LinkBoneIndex;						// 接続先ボーンインデックス
	int		AddParentBoneIndex;				// 付与親ボーンインデックス
	float	AddRatio;							// 付与率
	float	LockAxisVector[3];				// 軸固定時の軸の方向ベクトル
	float	LocalAxisXVector[3];				// ローカル軸のＸ軸
	float	LocalAxisZVector[3];				// ローカル軸のＺ軸
	int		OutParentTransformKey;				// 外部親変形時の Key値

	PMX_IK	IKInfo;							// ＩＫ情報
};

// 頂点モーフ情報
struct PMX_MORPH_VERTEX
{
	int		Index;								// 頂点インデックス
	float	Offset[3];						// 頂点座標オフセット
};

// ＵＶモーフ情報
struct PMX_MORPH_UV
{
	int		Index;								// 頂点インデックス
	FLOAT4	Offset;							// 頂点ＵＶオフセット
};

// ボーンモーフ情報
struct PMX_MORPH_BONE
{
	int		Index;								// ボーンインデックス
	float	Offset[3];						// 座標オフセット
	float	Quat[4];							// 回転クォータニオン
};

// 材質モーフ情報
struct PMX_MORPH_MATERIAL
{
	int		Index;								// マテリアルインデックス
	BYTE	CalcType;							// 計算タイプ( 0:乗算  1:加算 )
	float	Diffuse[4];						// ディフューズカラー
	float	Specular[3];						// スペキュラカラー
	float	SpecularPower;						// スペキュラ係数
	float	Ambient[3];						// アンビエントカラー
	float	EdgeColor[4];					// エッジカラー
	float	EdgeSize;							// エッジサイズ
	float	TextureScale[4];					// テクスチャ係数
	float	SphereTextureScale[4];			// スフィアテクスチャ係数
	float	ToonTextureScale[4];				// トゥーンテクスチャ係数
};

// グループモーフ
struct PMX_MORPH_GROUP
{
	int		Index;								// モーフインデックス
	float	Ratio;								// モーフ率
};

// モーフ情報
struct PMX_MORPH
{
	wchar_t	Name[128];						// 名前

	BYTE	ControlPanel;						// 操作パネル
	BYTE	Type;								// モーフの種類  0:グループ 1:頂点 2:ボーン 3:UV 4:追加UV1 5:追加UV2 6:追加UV3 7:追加UV4 8:材質

	int		DataNum;							// モーフ情報の数

	union
	{
		PMX_MORPH_VERTEX *Vertex;				// 頂点モーフ
		PMX_MORPH_UV *UV;						// UVモーフ
		PMX_MORPH_BONE *Bone;					// ボーンモーフ
		PMX_MORPH_MATERIAL *Material;			// マテリアルモーフ
		PMX_MORPH_GROUP *Group;				// グループモーフ
	};
};

// 剛体情報
struct PMX_RIGIDBODY
{
	wchar_t	Name[128];						// 名前

	int		BoneIndex;							// 対象ボーン番号

	BYTE	RigidBodyGroupIndex;				// 剛体グループ番号
	WORD	RigidBodyGroupTarget;				// 剛体グループ対象

	BYTE	ShapeType;							// 形状( 0:球  1:箱  2:カプセル )
	float	ShapeW;							// 幅
	float	ShapeH;							// 高さ
	float	ShapeD;							// 奥行

	float	Position[3];						// 位置
	float	Rotation[3];						// 回転( ラジアン )

	float	RigidBodyWeight;					// 質量
	float	RigidBodyPosDim;					// 移動減衰
	float	RigidBodyRotDim;					// 回転減衰
	float	RigidBodyRecoil;					// 反発力
	float	RigidBodyFriction;					// 摩擦力

	BYTE	RigidBodyType;						// 剛体タイプ( 0:Bone追従  1:物理演算  2:物理演算(Bone位置合わせ) )
};

// ジョイント情報
struct PMX_JOINT
{
	wchar_t	Name[128];						// 名前

	BYTE	Type;								// 種類( 0:スプリング6DOF ( PMX2.0 では 0 のみ )

	int		RigidBodyAIndex;					// 接続先剛体Ａ
	int		RigidBodyBIndex;					// 接続先剛体Ｂ

	float	Position[3];						// 位置
	float	Rotation[3];						// 回転( ラジアン )

	float	ConstrainPositionMin[3];			// 移動制限-下限
	float	ConstrainPositionMax[3];			// 移動制限-上限
	float	ConstrainRotationMin[3];			// 回転制限-下限
	float	ConstrainRotationMax[3];			// 回転制限-上限

	float	SpringPosition[3];				// バネ定数-移動
	float	SpringRotation[3];				// バネ定数-回転
};


typedef struct
{
	int				VertexNum;
	PMX_VERTEX		*Vertex;
}PMX;


// テキストデータをwchar_tに変換して取得
__inline void MV1LoadModelToPMX_GetString(BYTE **Src, wchar_t *DestBuffer, BYTE EncodeType)
{
	char Buffer[1024];
	wchar_t WBuffer[1024];
	DWORD TextSize;

	TextSize = GET_MEM_DWORD(*Src);
	*Src = *Src + 4;

	if (EncodeType == 0)
	{
		// UTF16

		_MEMCPY(WBuffer, *Src, TextSize);
		((BYTE *)WBuffer)[TextSize] = 0;
		((BYTE *)WBuffer)[TextSize + 1] = 0;
		*Src = *Src + TextSize;

		// UTF16を wchar_t に変換
		//ConvString((const char *)WBuffer, DX_CHARCODEFORMAT_UTF16LE, (char *)DestBuffer, BUFFERBYTES_CANCEL, WCHAR_T_CHARCODEFORMAT);
	}
	else
		if (EncodeType == 1)
		{
			// UTF8
			_MEMCPY(Buffer, *Src, TextSize);
			Buffer[TextSize] = '\0';
			*Src = *Src + TextSize;

			// UTF-8を wchar_t に変換
			//ConvString((const char *)Buffer, DX_CHARCODEFORMAT_UTF8, (char *)DestBuffer, BUFFERBYTES_CANCEL, WCHAR_T_CHARCODEFORMAT);
		}
}

// 整数値サイズに合わせた整数値を取得する(32bit以外符号なし)
__inline int MV1LoadModelToPMX_GetUInt(BYTE **Src, BYTE Size)
{
	int res = 0;

	switch (Size)
	{
	case 1:
		res = (int)((*Src)[0]);
		*Src = *Src + 1;
		break;

	case 2:
		res = (int)(((WORD *)*Src)[0]);
		*Src = *Src + 2;
		break;

	case 4:
		res = ((int *)*Src)[0];
		*Src = *Src + 4;
		break;
	}

	return res;
}


// 整数値サイズに合わせた整数値を取得する(符号あり)
__inline int MV1LoadModelToPMX_GetInt(BYTE **Src, BYTE Size)
{
	int res = 0;

	switch (Size)
	{
	case 1:
		res = GET_MEM_SIGNED_BYTE(*Src);
		*Src = *Src + 1;
		break;

	case 2:
		res = GET_MEM_SIGNED_WORD(*Src);
		*Src = *Src + 2;
		break;

	case 4:
		res = GET_MEM_SIGNED_DWORD(*Src);
		*Src = *Src + 4;
		break;
	}

	return res;
}


long GetFileSize(const char *file)
{
	struct stat statBuf;

	if (stat(file, &statBuf) == 0)
		return statBuf.st_size;

	return -1L;
}


//=============================================================================
// 読み込み処理
//=============================================================================
int LoadPmx(void)
{
	int NewHandle = -1;
	int ErrorFlag = 1;
	int i, j, k, weightcount, facecount;
	FILE *fp;
	BYTE *Src;
	BYTE *SrcFirst;
	PMX pmx;

	PMX_BASEINFO PmxInfo;
	BYTE AddHeadDataSize;
	DWORD PmxVertexNum;
	PMX_VERTEX *PmxVertex = NULL;
	DWORD PmxFaceNum;
	PMX_FACE *PmxFace = NULL;
	DWORD PmxTextureNum;
	PMX_TEXTURE *PmxTexture = NULL;
	DWORD PmxMaterialNum;
	PMX_MATERIAL *PmxMaterial = NULL;
	DWORD PmxBoneNum = 0;
	PMX_BONE *PmxBone = NULL;
	DWORD PmxIKNum;
	DWORD PmxSkinNum;
	DWORD PmxMorphNum;
	PMX_MORPH *PmxMorph = NULL;
	DWORD PmxRigidbodyNum;
	PMX_RIGIDBODY *PmxRigidbody = NULL;
	DWORD PmxJointNum;
	PMX_JOINT *PmxJoint = NULL;


	// ファイルサイズを確認
	long lFileSize = GetFileSize(FILE_PATH);
	printf("%d : ファイルサイズを確認\n", lFileSize);

	// ファイルを全て読み込むためのバッファを作る
	Src = new BYTE[lFileSize + 1];
	// 先頭アドレスを保管
	SrcFirst = Src;

	// バイナリ読み取りモードでファイルオープン
	fopen_s(&fp, FILE_PATH, "rb");
	if (fp == NULL) {
		printf("ファイルを開けません。\n");
		getchar();
		return -1;
	}

	// ファイルをバッファに読み込み
	fread(&*Src, lFileSize, 1, fp);

	// ファイルクローズ
	fclose(fp);

	// 末尾に念のため NULL を入れておく
	Src[lFileSize] = NULL;

	// PMXファイルかどうかを確認
	if (Src[0] != 'P' || Src[1] != 'M' || Src[2] != 'X' || Src[3] != ' ')
		return -1;
	Src += 4;

	// Ver2.0 かを確認
	if (Src[0] != 0x00 || Src[1] != 0x00 || Src[2] != 0x00 || Src[3] != 0x40)
	{
		printf("PMX Ver2.0ではない\n");
		return -1;
	}
	Src += 4;

	// 追加情報のサイズを取得
	AddHeadDataSize = Src[0];
	Src++;

	// 追加情報を取得
	PmxInfo.EncodeType = Src[0];
	PmxInfo.UVNum = Src[1];
	PmxInfo.VertexIndexSize = Src[2];
	PmxInfo.TextureIndexSize = Src[3];
	PmxInfo.MaterialIndexSize = Src[4];
	PmxInfo.BoneIndexSize = Src[5];
	PmxInfo.MorphIndexSize = Src[6];
	PmxInfo.RigidIndexSize = Src[7];
	Src += AddHeadDataSize;

	printf("%d : [0] - エンコード方式  | 0:UTF16 1:UTF8\n", PmxInfo.EncodeType);
	printf("%d : [1] - 追加UV数 	| 0～4 詳細は頂点参照\n", PmxInfo.UVNum);
	printf("%d : [2] - 頂点Indexサイズ | 1,2,4 のいずれか\n", PmxInfo.VertexIndexSize);
	printf("%d : [3] - テクスチャIndexサイズ | 1,2,4 のいずれか\n", PmxInfo.TextureIndexSize);
	printf("%d : [4] - 材質Indexサイズ | 1,2,4 のいずれか\n", PmxInfo.MaterialIndexSize);
	printf("%d : [5] - ボーンIndexサイズ | 1,2,4 のいずれか\n", PmxInfo.BoneIndexSize);
	printf("%d : [6] - モーフIndexサイズ | 1,2,4 のいずれか\n", PmxInfo.MorphIndexSize);
	printf("%d : [7] - 剛体Indexサイズ | 1,2,4 のいずれか\n", PmxInfo.RigidIndexSize);
	printf("\n");

	// モデル情報スキップ
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;

	// 頂点数を取得
	PmxVertexNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : 頂点数\n", PmxVertexNum);

	// 頂点データを格納するメモリ領域の確保
	PmxVertex = new PMX_VERTEX[PmxVertexNum];
	if (PmxVertex == NULL)
	{
		printf("メモリ確保に失敗：頂点\n");
		goto ENDLABEL;
	}

	// 頂点データを取得
	for (i = 0; (DWORD)i < PmxVertexNum; i++)
	{
		READ_MEM_4BYTE(&PmxVertex[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxVertex[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxVertex[i].Position[2], &Src[8]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[0], &Src[12]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[1], &Src[16]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[2], &Src[20]);
		READ_MEM_4BYTE(&PmxVertex[i].UV[0], &Src[24]);
		READ_MEM_4BYTE(&PmxVertex[i].UV[1], &Src[28]);
		Src += 32;

		//printf("pos[%2.2f, %2.2f, %2.2f]  nor[%2.2f, %2.2f, %2.2f]  uv[%2.2f, %2.2f]\n",
		//	PmxVertex[i].Position[0], PmxVertex[i].Position[1], PmxVertex[i].Position[2],
		//	PmxVertex[i].Normal[0], PmxVertex[i].Normal[1], PmxVertex[i].Normal[2],
		//	PmxVertex[i].UV[0], PmxVertex[i].UV[1]);

		for (j = 0; j < PmxInfo.UVNum; j++)
		{
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[12]);
			Src += 16;
		}

		PmxVertex[i].WeightType = Src[0];
		Src++;

		PmxVertex[i].BoneIndex[0] = -1;
		PmxVertex[i].BoneIndex[1] = -1;
		PmxVertex[i].BoneIndex[2] = -1;
		PmxVertex[i].BoneIndex[3] = -1;
		switch (PmxVertex[i].WeightType)
		{
		case 0:	// BDEF1
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneWeight[0] = 1.0f;
			break;

		case 1:	// BDEF2
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], Src);
			Src += 4;
			PmxVertex[i].BoneWeight[1] = 1.0f - PmxVertex[i].BoneWeight[0];
			break;

		case 2:	// BDEF4
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[2] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[3] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[1], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[2], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[3], &Src[12]);
			Src += 16;
			break;

		case 3:	// SDEF
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], Src);
			Src += 4;
			PmxVertex[i].BoneWeight[1] = 1.0f - PmxVertex[i].BoneWeight[0];
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[1], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[2], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[0], &Src[12]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[1], &Src[16]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[2], &Src[20]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[0], &Src[24]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[1], &Src[28]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[2], &Src[32]);
			Src += 36;
			break;
		}

		READ_MEM_4BYTE(&PmxVertex[i].ToonEdgeScale, Src);
		Src += 4;
	}

	// 面の数を取得
	PmxFaceNum = GET_MEM_DWORD(Src) / 3;
	Src += 4;
	printf("%d : 面数\n", PmxFaceNum);

	// 面データを格納するメモリ領域の確保
	PmxFace = new PMX_FACE[PmxFaceNum];
	if (PmxFace == NULL)
	{
		printf("メモリ確保に失敗：面\n");
		goto ENDLABEL;
	}

	// 面を構成する頂点インデックスの取得
	switch (PmxInfo.VertexIndexSize)
	{
	case 1:	// BYTE
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_BYTE(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_BYTE(&Src[1]);
			PmxFace[i].VertexIndex[2] = GET_MEM_BYTE(&Src[2]);
			Src += 3;
		}
		break;

	case 2:	// SHORT
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_WORD(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_WORD(&Src[2]);
			PmxFace[i].VertexIndex[2] = GET_MEM_WORD(&Src[4]);
			Src += 6;
		}
		break;

	case 4: // INT
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_DWORD(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_DWORD(&Src[4]);
			PmxFace[i].VertexIndex[2] = GET_MEM_DWORD(&Src[8]);
			Src += 12;
		}
		break;
	}

	// テクスチャの数を取得
	PmxTextureNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : テクスチャ数\n", PmxTextureNum);

	// テクスチャデータを格納するメモリ領域の確保
	PmxTexture = new PMX_TEXTURE[PmxTextureNum];
	if (PmxTexture == NULL)
	{
		printf("メモリ確保に失敗：テクスチャ\n");
		goto ENDLABEL;
	}

	// UTF16をひとまず表示させる
	//setlocale(LC_ALL, setlocale(LC_CTYPE, ""));

	// テクスチャの情報を取得
	for (i = 0; (DWORD)i < PmxTextureNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxTexture[i].TexturePath, PmxInfo.EncodeType);
		//wprintf(L"%s", PmxTexture[i].TexturePath);
	}

	// マテリアルの数を取得
	PmxMaterialNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : マテリアル数\n", PmxMaterialNum);

	// マテリアルデータを格納するメモリ領域の確保
	PmxMaterial = new PMX_MATERIAL[PmxMaterialNum];
	if (PmxMaterial == NULL)
	{
		printf("メモリ確保に失敗：マテリアル\n");
		goto ENDLABEL;
	}

	// マテリアルの読みこみ
	for (i = 0; (DWORD)i < PmxMaterialNum; i++)
	{
		// 材質名の取得
		MV1LoadModelToPMX_GetString(&Src, PmxMaterial[i].Name, PmxInfo.EncodeType);
		if (PmxMaterial[i].Name[0] == L'\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxMaterial[i].Name, PmxInfo.EncodeType);
			if (PmxMaterial[i].Name[0] == L'\0')
			{
				//_SWNPRINTF(PmxMaterial[i].Name, sizeof(PmxMaterial[i].Name) / 2, L"Mat_%d", i);
			}
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[2], &Src[8]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[3], &Src[12]);
		Src += 16;

		READ_MEM_4BYTE(&PmxMaterial[i].Specular[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Specular[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Specular[2], &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxMaterial[i].SpecularPower, &Src[0]);
		Src += 4;

		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[2], &Src[8]);
		Src += 12;

		PmxMaterial[i].CullingOff = (BYTE)((*Src & 0x01) ? 1 : 0);
		PmxMaterial[i].GroundShadow = (BYTE)((*Src & 0x02) ? 1 : 0);
		PmxMaterial[i].SelfShadowMap = (BYTE)((*Src & 0x04) ? 1 : 0);
		PmxMaterial[i].SelfShadowDraw = (BYTE)((*Src & 0x08) ? 1 : 0);
		PmxMaterial[i].EdgeDraw = (BYTE)((*Src & 0x10) ? 1 : 0);
		Src++;

		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[2], &Src[8]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[3], &Src[12]);
		Src += 16;

		READ_MEM_4BYTE(&PmxMaterial[i].EdgeSize, Src);
		Src += 4;

		PmxMaterial[i].TextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);
		PmxMaterial[i].SphereTextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);

		PmxMaterial[i].SphereMode = *Src;
		Src++;

		PmxMaterial[i].ToonFlag = *Src;
		Src++;
		if (PmxMaterial[i].ToonFlag == 0)
		{
			PmxMaterial[i].ToonTextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);
		}
		else
		{
			PmxMaterial[i].ToonTextureIndex = *Src;
			Src++;
		}

		// メモはスキップ
		Src += GET_MEM_DWORD(Src) + 4;

		PmxMaterial[i].MaterialFaceNum = GET_MEM_SIGNED_DWORD(Src);
		Src += 4;
	}

	// ボーンの数を取得
	PmxBoneNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : ボーン数\n", PmxBoneNum);

	// ボーンデータを格納するメモリ領域の確保
	PmxBone = new PMX_BONE[PmxBoneNum];
	if (PmxBone == NULL)
	{
		printf("メモリ確保に失敗：ボーン\n");
		goto ENDLABEL;
	}

	// ボーン情報の取得
	PmxIKNum = 0;
	for (i = 0; (DWORD)i < PmxBoneNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxBone[i].Name, PmxInfo.EncodeType);
		if (PmxBone[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxBone[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		READ_MEM_4BYTE(&PmxBone[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxBone[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxBone[i].Position[2], &Src[8]);
		Src += 12;

		PmxBone[i].ParentBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
		PmxBone[i].TransformLayer = GET_MEM_SIGNED_DWORD(Src);
		Src += 4;

		WORD Flag = GET_MEM_WORD(Src);
		Src += 2;
		PmxBone[i].Flag_LinkDest = (BYTE)((Flag & 0x0001) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableRot = (BYTE)((Flag & 0x0002) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableMov = (BYTE)((Flag & 0x0004) != 0 ? 1 : 0);
		PmxBone[i].Flag_Disp = (BYTE)((Flag & 0x0008) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableControl = (BYTE)((Flag & 0x0010) != 0 ? 1 : 0);
		PmxBone[i].Flag_IK = (BYTE)((Flag & 0x0020) != 0 ? 1 : 0);
		PmxBone[i].Flag_AddRot = (BYTE)((Flag & 0x0100) != 0 ? 1 : 0);
		PmxBone[i].Flag_AddMov = (BYTE)((Flag & 0x0200) != 0 ? 1 : 0);
		PmxBone[i].Flag_LockAxis = (BYTE)((Flag & 0x0400) != 0 ? 1 : 0);
		PmxBone[i].Flag_LocalAxis = (BYTE)((Flag & 0x0800) != 0 ? 1 : 0);
		PmxBone[i].Flag_AfterPhysicsTransform = (BYTE)((Flag & 0x1000) != 0 ? 1 : 0);
		PmxBone[i].Flag_OutParentTransform = (BYTE)((Flag & 0x2000) != 0 ? 1 : 0);

		if (PmxBone[i].Flag_LinkDest == 0)
		{
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[2], &Src[8]);
			Src += 12;
		}
		else
		{
			PmxBone[i].LinkBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
		}

		if (PmxBone[i].Flag_AddRot == 1 || PmxBone[i].Flag_AddMov == 1)
		{
			PmxBone[i].AddParentBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxBone[i].AddRatio, Src);
			Src += 4;
		}

		if (PmxBone[i].Flag_LockAxis == 1)
		{
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[2], &Src[8]);
			Src += 12;
		}

		if (PmxBone[i].Flag_LocalAxis == 1)
		{
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[2], &Src[8]);
			Src += 12;
		}

		if (PmxBone[i].Flag_OutParentTransform == 1)
		{
			PmxBone[i].OutParentTransformKey = GET_MEM_SIGNED_DWORD(Src);
			Src += 4;
		}

		if (PmxBone[i].Flag_IK == 1)
		{
			PmxIKNum++;

			PmxBone[i].IKInfo.TargetBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxBone[i].IKInfo.LoopNum = GET_MEM_SIGNED_DWORD(Src);
			Src += 4;

			READ_MEM_4BYTE(&PmxBone[i].IKInfo.RotLimit, Src);
			Src += 4;

			PmxBone[i].IKInfo.LinkNum = *((int *)Src);
			Src += 4;
			if (PmxBone[i].IKInfo.LinkNum >= PMX_MAX_IKLINKNUM)
			{
				printf("IKの上限値を超過：ボーン\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxBone[i].IKInfo.LinkNum; j++)
			{
				PmxBone[i].IKInfo.Link[j].BoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
				PmxBone[i].IKInfo.Link[j].RotLockFlag = Src[0];
				Src++;

				if (PmxBone[i].IKInfo.Link[j].RotLockFlag == 1)
				{
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[0], &Src[0]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[1], &Src[4]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[2], &Src[8]);
					Src += 12;

					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[0], &Src[0]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[1], &Src[4]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[2], &Src[8]);
					Src += 12;
				}
			}
		}
	}

	// モーフ情報の数を取得
	PmxMorphNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : モーフ数\n", PmxMorphNum);

	// モーフデータを格納するメモリ領域の確保
	PmxMorph = new PMX_MORPH[PmxMorphNum];
	if (PmxMorph == NULL)
	{
		printf("メモリ確保に失敗：モーフ\n");
		goto ENDLABEL;
	}

	// モーフ情報の読み込み
	PmxSkinNum = 0;
	for (i = 0; (DWORD)i < PmxMorphNum; i++)
	{
		PmxMorph[i].Group = NULL;
		PmxMorph[i].Vertex = NULL;
		PmxMorph[i].Bone = NULL;
		PmxMorph[i].UV = NULL;
		PmxMorph[i].Material = NULL;

		MV1LoadModelToPMX_GetString(&Src, PmxMorph[i].Name, PmxInfo.EncodeType);
		if (PmxMorph[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxMorph[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		PmxMorph[i].ControlPanel = Src[0];
		PmxMorph[i].Type = Src[1];
		PmxMorph[i].DataNum = GET_MEM_SIGNED_DWORD(&Src[2]);
		Src += 6;

		switch (PmxMorph[i].Type)
		{
		case 0:	// グループモーフ
			PmxMorph[i].Group = new PMX_MORPH_GROUP[PmxMorph[i].DataNum];
			if (PmxMorph[i].Group == NULL)
			{
				printf("メモリ確保に失敗：モーフグループ\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Group[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MorphIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Group[j].Ratio, Src);
				Src += 4;
			}
			break;

		case 1:	// 頂点
			PmxSkinNum++;
			PmxMorph[i].Vertex = new PMX_MORPH_VERTEX[PmxMorph[i].DataNum];
			if (PmxMorph[i].Vertex == NULL)
			{
				printf("メモリ確保に失敗：モーフ頂点\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Vertex[j].Index = MV1LoadModelToPMX_GetUInt(&Src, PmxInfo.VertexIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[2], &Src[8]);
				Src += 12;
			}
			break;

		case 2:	// ボーンモーフ
			PmxMorph[i].Bone = new PMX_MORPH_BONE[PmxMorph[i].DataNum];
			if (PmxMorph[i].Bone == NULL)
			{
				printf("メモリ確保に失敗：ボーンモーフ\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Bone[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[3], &Src[12]);
				Src += 16;
			}
			break;

		case 3:	// UVモーフ
		case 4:	// 追加UV1モーフ
		case 5:	// 追加UV2モーフ
		case 6:	// 追加UV3モーフ
		case 7:	// 追加UV4モーフ
			PmxMorph[i].UV = new PMX_MORPH_UV[PmxMorph[i].DataNum];
			if (PmxMorph[i].UV == NULL)
			{
				printf("メモリ確保に失敗：UVモーフ\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].UV[j].Index = MV1LoadModelToPMX_GetUInt(&Src, PmxInfo.VertexIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.x, &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.y, &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.z, &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.w, &Src[12]);
				Src += 16;
			}
			break;

		case 8:	// 材質モーフ
			PmxMorph[i].Material = new PMX_MORPH_MATERIAL[PmxMorph[i].DataNum];
			if (PmxMorph[i].Material == NULL)
			{
				printf("メモリ確保に失敗：マテリアルモーフ\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Material[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MaterialIndexSize);
				PmxMorph[i].Material[j].CalcType = Src[0];
				Src++;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SpecularPower, &Src[0]);
				Src += 4;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeSize, &Src[0]);
				Src += 4;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[3], &Src[12]);
				Src += 16;
			}
			break;
		}
	}

	// 表示枠データの読み込みはスキップ
	{
		DWORD PmxDispFrameNum;
		DWORD Num;
		BYTE Target;

		// 表示枠データの数を取得
		PmxDispFrameNum = GET_MEM_DWORD(Src);
		Src += 4;

		// 枠の数だけ繰り返し
		for (i = 0; (DWORD)i < PmxDispFrameNum; i++)
		{
			// 名前読み飛ばし
			Src += GET_MEM_DWORD(Src) + 4;
			Src += GET_MEM_DWORD(Src) + 4;

			// 特殊枠フラグ読み飛ばし
			Src++;

			// 枠内要素の数を取得
			Num = GET_MEM_DWORD(Src);
			Src += 4;

			// 枠内要素の読み飛ばし
			for (j = 0; (DWORD)j < Num; j++)
			{
				// 要素対象を取得
				Target = Src[0];
				Src++;

				// 要素対象によって処理を分岐
				switch (Target)
				{
				case 0:	// ボーンがターゲットの場合
					MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
					break;

				case 1:	// モーフがターゲットの場合
					MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MorphIndexSize);
					break;
				}
			}
		}
	}

	// 剛体情報の数を取得
	PmxRigidbodyNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : 剛体数\n", PmxRigidbodyNum);

	// 剛体データを格納するメモリ領域の確保
	PmxRigidbody = new PMX_RIGIDBODY[PmxRigidbodyNum];
	if (PmxRigidbody == NULL)
	{
		printf("メモリ確保に失敗：剛体\n");
		goto ENDLABEL;
	}

	// 剛体情報の読み込み
	for (i = 0; (DWORD)i < PmxRigidbodyNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxRigidbody[i].Name, PmxInfo.EncodeType);
		if (PmxRigidbody[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxRigidbody[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		PmxRigidbody[i].BoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);

		PmxRigidbody[i].RigidBodyGroupIndex = Src[0];
		Src++;

		READ_MEM_2BYTE(&PmxRigidbody[i].RigidBodyGroupTarget, Src);
		Src += 2;

		PmxRigidbody[i].ShapeType = Src[0];
		Src++;

		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeW, &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeH, &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeD, &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Position[2], &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[0], &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[1], &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[2], &Src[8]);
		if ((_FPCLASS(PmxRigidbody[i].Rotation[0]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[0] = 0.0f;
		if ((_FPCLASS(PmxRigidbody[i].Rotation[1]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[1] = 0.0f;
		if ((_FPCLASS(PmxRigidbody[i].Rotation[2]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[2] = 0.0f;
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyWeight, &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyPosDim, &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyRotDim, &Src[8]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyRecoil, &Src[12]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyFriction, &Src[16]);
		Src += 20;

		PmxRigidbody[i].RigidBodyType = Src[0];
		Src++;
	}

	// ジョイント情報の数を取得
	PmxJointNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : ジョイント数\n", PmxJointNum);

	// ジョイントデータを格納するメモリ領域の確保
	if (PmxJointNum != 0)
	{
		PmxJoint = new PMX_JOINT[PmxJointNum];
		if (PmxJoint == NULL)
		{
			printf("メモリ確保に失敗：ジョイント\n");
			goto ENDLABEL;
		}

		// ジョイント情報の読み込み
		for (i = 0; (DWORD)i < PmxJointNum; i++)
		{
			MV1LoadModelToPMX_GetString(&Src, PmxJoint[i].Name, PmxInfo.EncodeType);
			if (PmxJoint[i].Name[0] == '\0')
			{
				MV1LoadModelToPMX_GetString(&Src, PmxJoint[i].Name, PmxInfo.EncodeType);
			}
			else
			{
				Src += GET_MEM_DWORD(Src) + 4;
			}

			PmxJoint[i].Type = Src[0];
			Src++;

			PmxJoint[i].RigidBodyAIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.RigidIndexSize);
			PmxJoint[i].RigidBodyBIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.RigidIndexSize);

			READ_MEM_4BYTE(&PmxJoint[i].Position[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].Position[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].Position[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].Rotation[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].Rotation[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].Rotation[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[2], &Src[8]);
			Src += 12;
		}
	}




	//// エンコード方式がUTF16の場合
	//if (pmx.PmxInfo.EncodeType == 0)
	//{
	//	// wprintfでUTF16を表示できるようにする
	//	//setlocale(LC_ALL, "Japanese");
	//	setlocale(LC_ALL, setlocale(LC_CTYPE, ""));
	//}

	//// モデル情報を取得
	//for (UINT i = 0; i < MODEL_INFO_MAX; i++)
	//{
	//	fread(&pmx.ModelInfo[i].TxtSize, sizeof(pmx.ModelInfo[i].TxtSize), 1, fp);
	//	printf("%d : テキストバッファのサイズ\n", pmx.ModelInfo[i].TxtSize);

	//	if (pmx.ModelInfo[i].TxtSize > 0)
	//	{
	//		pmx.ModelInfo[i].Txt = new BYTE[pmx.ModelInfo[i].TxtSize];
	//		fread(&(*pmx.ModelInfo[i].Txt), sizeof(BYTE) * pmx.ModelInfo[i].TxtSize, 1, fp);

	//		wprintf(L"%s", pmx.ModelInfo[i].Txt);
	//		printf("\n");
	//	}
	//	printf("\n");
	//}
	//printf("\n");

ENDLABEL:
	SAFE_DELETE_ARRAY(SrcFirst);

	SAFE_DELETE_ARRAY(PmxJoint);
	SAFE_DELETE_ARRAY(PmxRigidbody);

	for (i = 0; (DWORD)i < PmxMorphNum; i++)
	{
		SAFE_DELETE_ARRAY(PmxMorph[i].Group);
		SAFE_DELETE_ARRAY(PmxMorph[i].Vertex);
		SAFE_DELETE_ARRAY(PmxMorph[i].Bone);
		SAFE_DELETE_ARRAY(PmxMorph[i].UV);
		SAFE_DELETE_ARRAY(PmxMorph[i].Material);
	}

	SAFE_DELETE_ARRAY(PmxMorph);
	SAFE_DELETE_ARRAY(PmxBone);
	SAFE_DELETE_ARRAY(PmxMaterial);
	SAFE_DELETE_ARRAY(PmxTexture);
	SAFE_DELETE_ARRAY(PmxVertex);
	return 0;
}
