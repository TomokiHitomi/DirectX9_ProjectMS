//=============================================================================
//
// ボックス処理 [box.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _BOX_H_
#define _BOX_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "stage.h"
#include "plane.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOX_TEXTURE				"data/TEXTURE/box3.png"						// 読み込むテクスチャファイル名

// テクスチャ内分割数
#define BOX_TEXTURE_PATTERN_DIVIDE_X	(1)
#define BOX_TEXTURE_PATTERN_DIVIDE_Y	(1)
// テクスチャ分割パターン
#define BOX_TEXTURE_PATTERN_NU	(BOX_TEXTURE_PATTERN_DIVIDE_X*BOX_TEXTURE_PATTERN_DIVIDE_Y)



// サイズ
#define	BOX_SIZE_X		(10.0f / 2)
#define	BOX_SIZE_Y		(10.0f / 2)
#define	BOX_SIZE		(8.0f / 2)

// 最大数
#define BOX_X_MAX		(15)
#define BOX_Z_MAX		(15)
#define BOX_Y_MAX		(5)

#define BOX_MARGIN		(20.0f)
#define BOX_HEIGHT		(10.0f)

// 最大数
//#define BOX_MAX		(((PLANE_X_MAX) * 2 + (PLANE_Y_MAX) * 2) * BOX_Y_MAX)
#define BOX_MAX		((BOX_X_MAX * 2 + BOX_Z_MAX * 2) * BOX_Y_MAX + BOX_X_MAX * BOX_Z_MAX)


#define BOX_ROT_SPEED	(0.03f)

#define BOX_ALPHA		(30)
#define BOX_COLOR_SPEED	(PLANE_COLOR_SPEED)
#define BOX_COLOR_MAX	(PLANE_COLOR_MAX)


//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Box
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
		float		angle;
		D3DCOLOR	diffuse;
	}INSTANCE_PLANE;

	LPDIRECT3DTEXTURE9				pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// 頂点バッファ
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// インスタンスバッファ
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// 頂点宣言

	// シェーダー関連
	LPD3DXEFFECT					pEffect;

	// 
	float							fRot;
	float							fColor;
	bool							bColor;


	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
public:

	Box();
	~Box();
	void Update(void);
	void Draw(void);
	void Release(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
