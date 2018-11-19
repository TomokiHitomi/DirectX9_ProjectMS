//=============================================================================
//
// プレイヤー処理 [gage.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _RESULTSELECT_H_
#define _RESULTSELECT_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_RESULTSELECT_000					"data/TEXTURE/retry010.png"												// gage hp
#define TEXTURE_RESULTSELECT_001					"data/TEXTURE/charselect010.png"										// gage hp
#define TEXTURE_RESULTSELECT_002					"data/TEXTURE/titleback010.png"											// gage hp



#define TEXTURE_RESULTSELECT_PIXEL000_X				(1000)																// ピクセルサイズ
#define TEXTURE_RESULTSELECT_PIXEL000_Y				(1000)																// ピクセルサイズ
#define TEXTURE_RESULTSELECT_PIXEL001_X				(1000)																// ピクセルサイズ
#define TEXTURE_RESULTSELECT_PIXEL001_Y				(1000)																// ピクセルサイズ
#define TEXTURE_RESULTSELECT_PIXEL002_X				(1000)																// ピクセルサイズ
#define TEXTURE_RESULTSELECT_PIXEL002_Y				(1000)																// ピクセルサイズ


#define TEXTURE_RESULTSELECT_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_RESULTSELECT_SIZE000_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_RESULTSELECT_SIZE001_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_RESULTSELECT_SIZE001_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_RESULTSELECT_SIZE002_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_RESULTSELECT_SIZE002_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_RESULTSELECT_SCALE_X				(1.0)																// 斜めサイズ
#define TEXTURE_RESULTSELECT_SCALE_Y				(1.0)																// 斜めサイズ


#define TEXTURE_RESULTSELECT_SIZE000_X				(TEXTURE_RESULTSELECT_SIZE000_LATE_X*SCREEN_WIDTH/4)						// サイズ
#define TEXTURE_RESULTSELECT_SIZE000_Y				(TEXTURE_RESULTSELECT_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_RESULTSELECT_SIZE001_X				(TEXTURE_RESULTSELECT_SIZE001_LATE_X*SCREEN_WIDTH/4)						// サイズ
#define TEXTURE_RESULTSELECT_SIZE001_Y				(TEXTURE_RESULTSELECT_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_RESULTSELECT_SIZE002_X				(TEXTURE_RESULTSELECT_SIZE002_LATE_X*SCREEN_WIDTH/4)						// サイズ
#define TEXTURE_RESULTSELECT_SIZE002_Y				(TEXTURE_RESULTSELECT_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// サイズ

#define TEXTURE_RESULTSELECT_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_RESULTSELECT_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション
#define TEXTURE_RESULTSELECT_OFFSET_POSITION001_X	(0.0f)																// オフセットポジション
#define TEXTURE_RESULTSELECT_OFFSET_POSITION001_Y	(TEXTURE_RESULTSELECT_SIZEADD_Y)											// オフセットポジション


#define TEXTURE_RESULTSELECT_POSITION000_X			(TEXTURE_RESULTSELECT_OFFSET_POSITION000_X+SCREEN_WIDTH/2)					// ポジション
#define TEXTURE_RESULTSELECT_POSITION000_Y			(TEXTURE_RESULTSELECT_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2-TEXTURE_RESULTSELECT_SIZE000_Y)	// ポジション
#define TEXTURE_RESULTSELECT_POSITION001_X			(TEXTURE_RESULTSELECT_POSITION000_X)	// ポジション
#define TEXTURE_RESULTSELECT_POSITION001_Y			(TEXTURE_RESULTSELECT_POSITION000_Y+TEXTURE_RESULTSELECT_SIZE000_Y*2)	// ポジション
#define TEXTURE_RESULTSELECT_POSITION002_X			(TEXTURE_RESULTSELECT_POSITION000_X)										// ポジション
#define TEXTURE_RESULTSELECT_POSITION002_Y			(TEXTURE_RESULTSELECT_POSITION000_Y+TEXTURE_RESULTSELECT_SIZE000_Y*4)										// ポジション
#define TEXTURE_RESULTSELECT_ANGLE_X				(0.0)																// ポジション



#define TEXTURE_RESULTSELECT_COLOR_DEFAULT000_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT000_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT000_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT000_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT001_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT001_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT001_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT001_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT002_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT002_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT002_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_DEFAULT002_A		(255)																// テクスチャ頂点カラー変化前

#define TEXTURE_RESULTSELECT_COLOR_CHANGE_R			(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_RESULTSELECT_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define NUM_RESULTSELECT							(3)																// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Resultselect : public ObjectManager
{
public:


	struct ResultselectParts
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
	ResultselectParts ResultselectObj[NUM_RESULTSELECT];
	void SetVertexResultselect(int CreateCount);
	void SetTextureResultselect(int i);
	HRESULT MakeVertexResultselect(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Resultselect();
	~Resultselect();
};


#endif
