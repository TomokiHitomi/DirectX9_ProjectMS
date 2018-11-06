//=============================================================================
//
// プレイヤー処理 [titlemesh.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _TITLEMESH_H_
#define _TITLEMESH_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_TITLEMESH_000					"data/TEXTURE/logo001.png"											// ロゴ

#define FIELD_NUM_X		(100)
#define FIELD_NUM_Z		(100)

#define FIELD_BLOCK_SIZE_X		(50.0f)
#define FIELD_BLOCK_SIZE_Z		(50.0f)

#define FIELD_RANGE_X		(FIELD_NUM_X*FIELD_BLOCK_SIZE_X)
#define FIELD_RANGE_Z		(FIELD_NUM_Z*FIELD_BLOCK_SIZE_Z)

#define TEXTURE_TITLEMESH_PIXEL000_X			(1167)																// ピクセルサイズ
#define TEXTURE_TITLEMESH_PIXEL000_Y			(1152)																// ピクセルサイズ

#define TEXTURE_TITLEMESH_SIZE000_LATE_X		(1.0)																// 拡大倍率
#define TEXTURE_TITLEMESH_SIZE000_LATE_Y		(0.6)																// 拡大倍率
#define TEXTURE_TITLEMESH_SIZE000_X				(TEXTURE_TITLEMESH_SIZE000_LATE_X*TEXTURE_TITLEMESH_PIXEL000_X)		// サイズ
#define TEXTURE_TITLEMESH_SIZE000_Y				(TEXTURE_TITLEMESH_SIZE000_LATE_Y*TEXTURE_TITLEMESH_PIXEL000_Y)		// サイズ
#define TEXTURE_TITLEMESH_POSITION000_X			(0)													// ポジション
#define TEXTURE_TITLEMESH_POSITION000_Y			(0)												// ポジション
#define TEXTURE_TITLEMESH_POSITION000_Z			(0)												// ポジション
#define TEXTURE_TITLEMESH_ROTATION000_X			(0)													// ポジション
#define TEXTURE_TITLEMESH_ROTATION000_Y			(0)												// ポジション
#define TEXTURE_TITLEMESH_ROTATION000_Z			(0)												// ポジション

#define TEXTURE_TITLEMESH_COLOR_DEFAULT_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_A		(255)																// テクスチャ頂点カラー変化前
#define NUM_TITLEMESH							(1)																	// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Titlemesh : public ObjectManager
{
public:


	struct TitlemeshParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		D3DXVECTOR3				Rot;									// プレイヤーの移動量
		D3DXVECTOR3				Scale;									// プレイヤーの移動量
		D3DXMATRIX				WorldMatrix;							// ワールドマトリックス
		LPD3DXMESH				pD3DXMesh;								// メッシュ情報へのポインタ
		LPD3DXBUFFER			pD3DXBuffMat;							// マテリアル情報へのポインタ
		LPDIRECT3DVERTEXBUFFER9	lpD3DVertexBuffer;
		LPDIRECT3DINDEXBUFFER9	lpD3DIndexBuffer;						// Direct3DIndexBuffer8 オブジェクト
		LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
		LPDIRECT3DINDEXBUFFER9	pD3DIdxBuff;		// インデックスバッファインターフェースへのポインタ
		DWORD					nNumMatGround;							// マテリアル情報の数
		VERTEX_2D				vertexWk[NUM_VERTEX];					// 頂点情報格納ワーク
		D3DXVECTOR2				TextureSize;
		int						NumVertex;								// 総頂点数
		int						NumVertexIndex;							// 総インデックス数
		int						NumPolygon;								// 総ポリゴン数
		int						NumBlockX;
		int						NumBlockZ;
		float					BlockSizeX;
		float					BlockSizeZ;
		int						Count;
		int						Alfa;
		bool					Flash;
		bool					Use;									// true:使用  false:未使用
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
	};
	TitlemeshParts TitleMesh[NUM_TITLEMESH];
	void SetVertexTitlemesh(int CreateCount);
	void SetTextureTitlemesh(int i);
	HRESULT MakeVertexTitlemesh(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlemesh();
	~Titlemesh();
};


#endif
