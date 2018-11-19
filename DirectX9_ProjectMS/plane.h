//=============================================================================
//
// プレーン処理 [plane.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "stage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLANE_TEXTURE				"data/TEXTURE/white_1x1.png"						// 読み込むテクスチャファイル名

// テクスチャ内分割数
#define PLANE_TEXTURE_PATTERN_DIVIDE_X	(1)
#define PLANE_TEXTURE_PATTERN_DIVIDE_Y	(1)
// テクスチャ分割パターン\
#define PLANE_TEXTURE_PATTERN_NU	(PLANE_TEXTURE_PATTERN_DIVIDE_X*PLANE_TEXTURE_PATTERN_DIVIDE_Y)

#define PLANE_MARGIN	(0.8f)

// サイズ
#define	PLANE_SIZE_X		(10.0f / 2)
#define	PLANE_SIZE_Y		(10.0f / 2)

// 最大数
#define PLANE_X_MAX		(25)
#define PLANE_Y_MAX		(25)

// 最大数
#define PLANE_MAX			(PLANE_X_MAX * PLANE_Y_MAX)

#define PLANE_COLOR_SPEED	(0.003f)
#define PLANE_COLOR_MAX		(0.1f)


//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Plane
{
private:
	typedef struct
	{
		D3DXVECTOR4 vtx;
		D3DXVECTOR2 tex;
	}VERTEX_PLANE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DCOLOR	diffuse;
	}INSTANCE_PLANE;

	LPDIRECT3DTEXTURE9				pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// 頂点バッファ
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// インスタンスバッファ
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// 頂点宣言

	// シェーダー関連
	LPD3DXEFFECT					pEffect;

	float							fColor;
	bool							bColor;


	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
public:

	Plane();
	~Plane();
	void Update(void);
	void Draw(void);
	void Release(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
