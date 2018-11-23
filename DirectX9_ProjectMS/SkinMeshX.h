//=============================================================================
//
// アニメーションモデル処理 [SkinMeshX.h]
// Author : GP12A295 25 人見友基
//
// 参考：GESブログ
// http://ges.blog.shinobi.jp/directx/directx%209%E3%80%80%E3%82%B9%E3%82%AD%E3%83%B3%E3%83%A1%E3%83%83%E3%82%B7%E3%83%A5%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0
//
//=============================================================================
#ifndef _SKINMESHX_H_
#define _SKINMESHX_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "shader.h"
#include <vector>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define SKIN_ANIME_SPEED	(60.0f / 4800.0f)
#define SKIN_ANIME_SPEED	(60.0f / 3000.0f)
#define SKIN_ANIME_WEIGHT	(0.05f)

#define ANIMATION_SET_MAX	(25)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
}PRS;// Pos Rot Scl

//struct MYFRAME : public D3DXFRAME
//{
//	D3DXMATRIX CombinedTransformationMatrix;
//	// オフセット行列(インデックス付描画用)
//	D3DXMATRIX OffsetMat;
//	// 行列テーブルのインデックス番号(インデックス付用)
//	DWORD OffsetID;
//};

//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
//struct MYMESHCONTAINER : public D3DXMESHCONTAINER
//{
//	LPDIRECT3DTEXTURE9*  ppTextures;
//	DWORD dwWeight; //重みの個数（重みとは頂点への影響。）
//	DWORD dwBoneNum; //ボーンの数
//	LPD3DXBUFFER pBoneBuffer; //ボーン・テーブル
//	D3DXMATRIX** ppBoneMatrix; //全てのボーンのワールド行列の先頭ポインター
//	D3DXMATRIX* pBoneOffsetMatrices; //フレームとしてのボーンのワールド行列のポインター
//	LPD3DXMESH pOriMesh; //オリジナルメッシュ用
//	DWORD NumPaletteEntries; //パレットサイズ
//	// Work用
//	//std::vector<D3DXMATRIX> m_WorkBoneMatArray;
//	// 影響するフレームへの参照配列。描画時にこのフレームの行列を使う。
//	//std::vector<MYFRAME*> BoneFrameArray;
//	MYMESHCONTAINER() {
//		ppBoneMatrix = NULL;
//		pBoneOffsetMatrices = NULL;
//	}
//};


//--------------------------------------------------------------------------------------
// Name: struct D3DXFRAME_DERIVED
// Desc: Structure derived from D3DXFRAME so we can add some app-specific
//       info that will be stored with each frame
//--------------------------------------------------------------------------------------
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9* ppTextures;       // array of textures, entries are NULL if no texture specified    

	// SkinMesh info             
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning
	
	D3DXMESHCONTAINER_DERIVED()
	{
		ppBoneMatrixPtrs = NULL;
		pBoneOffsetMatrices = NULL;
	}
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
// Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
// ID3DXAllocateHierarchyは派生すること想定して設計されている。
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:
};

// スキンメッシュクラス
class CSkinMesh
{
public:
	//メッシュクラスの初期化
	// VOID InitBase(SMESH_DATA_FILE* _pSMeshData);
	//メッシュの現在のMatrixデータ取得
	bool GetMatrix(D3DXMATRIX* out, int dwCon, int dwBone);

	CSkinMesh();
	~CSkinMesh() {
		Release();
	}
	//スキンメッシュ内部処理
	HRESULT Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	VOID RenderMeshContainer(LPDIRECT3DDEVICE9 lpD3DDevice, D3DXMESHCONTAINER_DERIVED*, D3DXFRAME_DERIVED*);
	VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	VOID DrawFrame(PDIRECT3DDEVICE9 lpD3DDevice, LPD3DXFRAME pFrameBase);
	//フレーム解放
	VOID FreeAnim(LPD3DXFRAME pFrame);
	//解放処理
	VOID Release();
	//更新処理
	VOID Update(void);
	//描画処理
	VOID Draw(LPDIRECT3DDEVICE9 lpD3DDevice, D3DXMATRIX _World);
	//オブジェクトのアニメーション変更( メッシュオブジェクトの操作用番号, 変更するアニメーション番号 )
	VOID CSkinMesh::ChangeAnim(DWORD _NewAnimNum, FLOAT fShift);
	//現在のアニメーション番号取得
	DWORD GetAnimTrack() { return m_CurrentTrack; }
	//現在のアニメーションタイム(アニメーション開始からの時間)を取得
	DWORD GetAnimTime() { return m_AnimeTime; }
	//アニメーション速度を取得
	FLOAT GetAnimSpeed() { return m_AnimSpeed; }
	//アニメーション速度を設定
	VOID SetAnimSpeed(FLOAT _AnimSpeed) { m_AnimSpeed = _AnimSpeed; }
	//アニメーションタイムを設定
	VOID SetAnimTime(DWORD _AnimeTime) { m_AnimeTime = _AnimeTime; }
private:
	//対象のボーンを検索
	D3DXFRAME_DERIVED* SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame);
public:
	//ボーンのマトリックス取得( ボーンの名前 )
	D3DXMATRIX GetBoneMatrix(LPSTR _BoneName);
	//ボーンのマトリックスポインタ取得( ボーンの名前 )
	D3DXMATRIX* GetpBoneMatrix(LPSTR _BoneName);

	DWORD	m_dwContainerCount;			// ボーン数カウント
	DWORD	m_dwBoneCount;			// ボーン数カウント
private:
	//追加
	//すべてのフレームポインタ格納処理関数
	VOID CreateFrameArray(LPD3DXFRAME _pFrame);
	// フレーム参照用配列
	std::vector<D3DXFRAME_DERIVED*> m_FrameArray; // 全フレーム参照配列
	std::vector<D3DXFRAME_DERIVED*> m_IntoMeshFrameArray;// メッシュコンテナありのフレーム参照配列
	//ボーン情報
	LPD3DXFRAME m_pFrameRoot;
	//アニメーションコントローラ
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	//ヒエラルキークラス変数
	MY_HIERARCHY m_cHierarchy;
	//アニメーションデータ格納用変数(ここは可変に変更したほうがいい)
	LPD3DXANIMATIONSET m_pAnimSet[ANIMATION_SET_MAX];
	//現在のアニメーションが開始されてからの時間(1/60秒)
	DWORD m_AnimeTime;
	//アニメーションスピード
	FLOAT m_AnimSpeed;
	//現在のアニメーショントラック
	DWORD m_CurrentTrack;
	//現在のアニメーションデータトラック
	D3DXTRACK_DESC m_CurrentTrackDesc;
	//進行方向
	D3DXMATRIX m_World;
	//メッシュのマテリアル関係
	//マテリアル変更フラグ
	BOOL m_MaterialFlg;
	//マテリアルデータ
	D3DMATERIAL9 m_Material;

	// シェーダ用
	LPD3DXEFFECT	pEffect;


	// モーションブレンド用追加プロパティ
	FLOAT	m_fShiftTime;			// シフトするのにかかる時間
	FLOAT	m_fCurWeight;			// 現在のウェイト時間
	DWORD	m_OldTrack;				// 変更前アニメーショントラック
};
#endif