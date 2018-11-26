//=============================================================================
//
// プレイヤー処理 [ko.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _WINNERLOGO_H_
#define _WINNERLOGO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_WINNERLOGO_000					"data/TEXTURE/winner002.png"											// gage hp
#define TEXTURE_WINNERLOGO_001					"data/TEXTURE/winner002.png"											// gage hp



#define TEXTURE_WINNERLOGO_PIXEL000_X				(200)																// ピクセルサイズ
#define TEXTURE_WINNERLOGO_PIXEL000_Y				(50)																// ピクセルサイズ
#define TEXTURE_WINNERLOGO_PIXEL001_X				(200)																// ピクセルサイズ
#define TEXTURE_WINNERLOGO_PIXEL001_Y				(50)																// ピクセルサイズ


#define TEXTURE_WINNERLOGO_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE000_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE001_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE001_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE002_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE002_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE003_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_WINNERLOGO_SIZE003_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_WINNERLOGO_SCALE_X					(1.0)																// 斜めサイズ
#define TEXTURE_WINNERLOGO_SCALE_Y					(1.0)																// 斜めサイズ


#define TEXTURE_WINNERLOGO_SIZE000_X				(TEXTURE_WINNERLOGO_SIZE000_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_WINNERLOGO_PIXEL000_X)						// サイズ
#define TEXTURE_WINNERLOGO_SIZE000_Y				(TEXTURE_WINNERLOGO_SIZE000_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_WINNERLOGO_PIXEL000_Y)						// サイズ
#define TEXTURE_WINNERLOGO_SIZE001_X				(TEXTURE_WINNERLOGO_SIZE001_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_WINNERLOGO_PIXEL001_X)					// サイズ
#define TEXTURE_WINNERLOGO_SIZE001_Y				(TEXTURE_WINNERLOGO_SIZE001_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_WINNERLOGO_PIXEL001_Y)						// サイズ


#define TEXTURE_WINNERLOGO_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION001_X	(0.0f)																// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION001_Y	(0.0f)											// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION002_X	(0.0f)																// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION002_Y	(0.0f)											// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION003_X	(0.0f)																// オフセットポジション
#define TEXTURE_WINNERLOGO_OFFSET_POSITION003_Y	(0.0f)											// オフセットポジション


#define TEXTURE_WINNERLOGO_POSITION000_X			(TEXTURE_WINNERLOGO_OFFSET_POSITION000_X+SCREEN_WIDTH/2+SCREEN_WIDTH/4)					// ポジション
#define TEXTURE_WINNERLOGO_POSITION000_Y			(TEXTURE_WINNERLOGO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// ポジション
#define TEXTURE_WINNERLOGO_POSITION001_X			(TEXTURE_WINNERLOGO_OFFSET_POSITION001_X+SCREEN_WIDTH)	// ポジション
#define TEXTURE_WINNERLOGO_POSITION001_Y			(TEXTURE_WINNERLOGO_OFFSET_POSITION001_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// ポジション
#define TEXTURE_WINNERLOGO_ANGLE_X				(0.0)																		// ポジション



#define TEXTURE_WINNERLOGO_COLOR_DEFAULT000_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT000_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT000_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT000_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT001_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT001_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT001_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT001_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT002_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT002_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT002_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT002_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT003_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT003_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT003_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_DEFAULT003_A		(255)																// テクスチャ頂点カラー変化前

#define TEXTURE_WINNERLOGO_COLOR_CHANGE_R			(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_SCOND						(3)																// テクスチャ頂点カラー変化前
#define TEXTURE_WINNERLOGO_SCOND_COUNT				(2)
#define TEXTURE_WINNERLOGO_SCOND_COUNT_COLOR			(255.0f /TEXTURE_WINNERLOGO_SCOND_COUNT)
#define TEXTURE_WINNERLOGO_SCOND_TIME				(FRAME*TEXTURE_WINNERLOGO_SCOND)									//300
#define TEXTURE_WINNERLOGO_SCOND_COLOR				(TEXTURE_WINNERLOGO_SCOND_COUNT_COLOR/TEXTURE_WINNERLOGO_SCOND_TIME)								//90
#define WINNER_TIME									(FRAME/2)
#define NUM_WINNERLOGO								(2)																// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Winnerlogo : public ObjectManager
{
public:


	struct WinnerlogoParts
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
		float					Color;
		bool					Use;									// true:使用  false:未使用
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
		bool					Nowselect;
	};
	WinnerlogoParts WinnerlogoObj[NUM_WINNERLOGO];
	void SetVertexWinnerlogo(int CreateCount);
	void SetTextureWinnerlogo(int i);
	HRESULT MakeVertexWinnerlogo(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Starttime(void);
	Winnerlogo();
	~Winnerlogo();
	void Set(void);
};


#endif
