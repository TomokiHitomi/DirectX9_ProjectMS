//=============================================================================
//
// プレイヤー処理 [gary.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _GRAY_H_
#define _GRAY_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_GRAY_000					"data/TEXTURE/white_1x1.png"												// gage hp




#define TEXTURE_GRAY_PIXEL000_X				(1)																// ピクセルサイズ
#define TEXTURE_GRAY_PIXEL000_Y				(1)																// ピクセルサイズ

#define TEXTURE_GRAY_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GRAY_SIZE000_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_GRAY_SCALE_X				(1.0)																// 斜めサイズ
#define TEXTURE_GRAY_SCALE_Y				(1.0)																// 斜めサイズ


#define TEXTURE_GRAY_SIZE000_X				(TEXTURE_GRAY_SIZE000_LATE_X*SCREEN_WIDTH)						// サイズ
#define TEXTURE_GRAY_SIZE000_Y				(TEXTURE_GRAY_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// サイズ


#define TEXTURE_GRAY_SIZE001_X				(TEXTURE_GRAY_SIZE000_LATE_X*SCREEN_WIDTH/4)						// サイズ
#define TEXTURE_GRAY_SIZE001_Y				(TEXTURE_GRAY_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// サイズ
#define TEXTURE_GRAY_SIZE002_X				(TEXTURE_GRAY_SIZE000_LATE_X*SCREEN_WIDTH/4)						// サイズ
#define TEXTURE_GRAY_SIZE002_Y				(TEXTURE_GRAY_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// サイズ

#define TEXTURE_GRAY_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_GRAY_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション


#define TEXTURE_GRAY_POSITION000_X			(TEXTURE_GRAY_OFFSET_POSITION000_X+SCREEN_WIDTH/2)					// ポジション
#define TEXTURE_GRAY_POSITION000_Y			(TEXTURE_GRAY_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// ポジション
#define TEXTURE_GRAY_POSITION001_X			(TEXTURE_GRAY_OFFSET_POSITION000_X+SCREEN_WIDTH/4)					// ポジション
#define TEXTURE_GRAY_POSITION001_Y			(TEXTURE_GRAY_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// ポジション
#define TEXTURE_GRAY_POSITION002_X			(TEXTURE_GRAY_OFFSET_POSITION000_X+SCREEN_WIDTH/2+SCREEN_WIDTH/4)					// ポジション
#define TEXTURE_GRAY_POSITION002_Y			(TEXTURE_GRAY_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// ポジション
#define TEXTURE_GRAY_ANGLE_X				(0.0)																// ポジション



#define TEXTURE_GRAY_COLOR_DEFAULT000_R		(0)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_DEFAULT000_G		(0)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_DEFAULT000_B		(0)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_DEFAULT000_A		(127)																// テクスチャ頂点カラー変化前

#define TEXTURE_GRAY_COLOR_CHANGE_R			(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_GRAY_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define NUM_GRAY							(3)																// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Gray : public ObjectManager
{
public:


	struct GrayParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		VERTEX_2D				vertexWk[NUM_VERTEX];					// 頂点情報格納ワーク
		D3DXVECTOR2				TextureSize;
		D3DXVECTOR2				TextureSizeAdd;
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		bool					Use;									// true:使用  false:未使用
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
		bool					Nowselect;
	};
	GrayParts GrayObj[NUM_GRAY];
	void SetVertexGray(int CreateCount);
	void SetTextureGray(int i);
	HRESULT MakeVertexGray(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Gray();
	~Gray();
};


#endif
