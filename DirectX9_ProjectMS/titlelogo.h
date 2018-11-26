//=============================================================================
//
// プレイヤー処理 [titlelogo.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_TITLELOGO_000					"data/TEXTURE/logo001.png"											// ロゴ
#define TEXTURE_TITLELOGO_001					"data/TEXTURE/start001.png"											// ロゴ

#define TEXTURE_TITLELOGO_PIXEL000_X			(1167/2*SCREEN_SCALE)																// ピクセルサイズ
#define TEXTURE_TITLELOGO_PIXEL000_Y			(1152/2*SCREEN_SCALE)																// ピクセルサイズ
#define TEXTURE_TITLELOGO_PIXEL001_X			(500/2*SCREEN_SCALE)																// ピクセルサイズ
#define TEXTURE_TITLELOGO_PIXEL001_Y			(146/2*SCREEN_SCALE)																// ピクセルサイズ

#define TEXTURE_TITLELOGO_SIZE000_LATE_X		(1.0)																// 拡大倍率
#define TEXTURE_TITLELOGO_SIZE000_LATE_Y		(0.6)																// 拡大倍率
#define TEXTURE_TITLELOGO_SIZE001_LATE_X		(0.5)																// 拡大倍率
#define TEXTURE_TITLELOGO_SIZE001_LATE_Y		(0.5)																// 拡大倍率
#define TEXTURE_TITLELOGO_SIZE000_X				(TEXTURE_TITLELOGO_SIZE000_LATE_X*TEXTURE_TITLELOGO_PIXEL000_X)		// サイズ
#define TEXTURE_TITLELOGO_SIZE000_Y				(TEXTURE_TITLELOGO_SIZE000_LATE_Y*TEXTURE_TITLELOGO_PIXEL000_Y)		// サイズ
#define TEXTURE_TITLELOGO_SIZE001_X				(TEXTURE_TITLELOGO_SIZE001_LATE_X*TEXTURE_TITLELOGO_PIXEL001_X)		// サイズ
#define TEXTURE_TITLELOGO_SIZE001_Y				(TEXTURE_TITLELOGO_SIZE001_LATE_Y*TEXTURE_TITLELOGO_PIXEL001_Y)		// サイズ
#define TEXTURE_TITLELOGO_POSITION000_X			(SCREEN_WIDTH/2)													// ポジション
#define TEXTURE_TITLELOGO_POSITION000_Y			(SCREEN_HEIGHT/2.8)												// ポジション
#define TEXTURE_TITLELOGO_POSITION001_X			(SCREEN_WIDTH/2)													// ポジション
#define TEXTURE_TITLELOGO_POSITION001_Y			(SCREEN_HEIGHT/1.20)												// ポジション

#define TEXTURE_TITLELOGO_COLOR_DEFAULT_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_A		(255)																// テクスチャ頂点カラー変化前
#define NUM_TITLELOGO							(2)																	// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Titlelogo : public ObjectManager
{
public:


	struct TitlelogoParts
	{
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		VERTEX_2D				vertexWk[NUM_VERTEX];					// 頂点情報格納ワーク
		D3DXVECTOR2				TextureSize;
		int						Count;
		int						Alfa;
		bool					Flash;
		bool					Use;									// true:使用  false:未使用
	};
	TitlelogoParts Title[NUM_TITLELOGO];
	void SetVertexTitlelogo(int CreateCount);
	void SetTextureTitlelogo(int i);
	HRESULT MakeVertexTitlelogo(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlelogo();
	~Titlelogo();
};


#endif
