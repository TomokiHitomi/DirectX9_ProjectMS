//=============================================================================
//
// プレイヤー処理 [ko.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_TIME_000					"data/TEXTURE/time001.png"											// gage hp



#define TEXTURE_TIME_PIXEL000_X				(50)																// ピクセルサイズ
#define TEXTURE_TIME_PIXEL000_Y				(50)																// ピクセルサイズ


#define TEXTURE_TIME_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_TIME_SIZE000_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_TIME_SCALE_X				(1.0)																// 斜めサイズ
#define TEXTURE_TIME_SCALE_Y				(1.0)																// 斜めサイズ


#define TEXTURE_TIME_SIZE000_X				(TEXTURE_TIME_SIZE000_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_TIME_PIXEL000_X*1.75/2*SCREEN_SCALE)						// サイズ
#define TEXTURE_TIME_SIZE000_Y				(TEXTURE_TIME_SIZE000_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_TIME_PIXEL000_Y*1.75/2*SCREEN_SCALE)						// サイズ


#define TEXTURE_TIME_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_TIME_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション


#define TEXTURE_TIME_POSITION000_X			(TEXTURE_TIME_OFFSET_POSITION000_X+SCREEN_WIDTH/2)					// ポジション
#define TEXTURE_TIME_POSITION000_Y			(TEXTURE_TIME_OFFSET_POSITION000_Y+SCREEN_HEIGHT*0.005)	// ポジション
#define TEXTURE_TIME_ANGLE_X				(0.0)																		// ポジション



#define TEXTURE_TIME_COLOR_DEFAULT000_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_DEFAULT000_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_DEFAULT000_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_DEFAULT000_A		(255)																// テクスチャ頂点カラー変化前

#define TEXTURE_TIME_COLOR_CHANGE_R			(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_SCOND					(3)																// テクスチャ頂点カラー変化前
#define TEXTURE_TIME_SCOND_COUNT			(2)
#define TEXTURE_TIME_SCOND_COUNT_COLOR		(255.0f /TEXTURE_TIME_SCOND_COUNT)
#define TEXTURE_TIME_SCOND_TIME				(FRAME*TEXTURE_TIME_SCOND)									//300
#define TEXTURE_TIME_SCOND_COLOR			(TEXTURE_TIME_SCOND_COUNT_COLOR/TEXTURE_TIME_SCOND_TIME)								//90
#define TEXTURE_TIME_TIME_000				(FRAME)								//90
#define TEXTURE_TIME_DIGIT					(2)							// 桁数
#define TEXTURE_TIME_MAX					(99)						// スコアの最大値
#define TEXTURE_TIME_SECOND					(20)
#define NUM_TIME							(1)																// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Time : public ObjectManager
{
public:


	struct TimeParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		//VERTEX_2D				vertexWk[NUM_VERTEX];					// 頂点情報格納ワーク
		VERTEX_2D				vertexWk[TEXTURE_TIME_DIGIT][NUM_VERTEX];
		D3DXVECTOR2				TextureSize;
		D3DXVECTOR2				TextureSizeAdd;
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		int						Timer;
		float					Color;
		bool					Use;									// true:使用  false:未使用
		bool					Start;
		bool					End;
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
		int 					Nowselect;
	};
	TimeParts TimeObj[NUM_TIME];
	void SetVertexTime(int CreateCount);
	void SetTextureTime(void);
	bool GetEnd(void);
	void SetStart(bool flag);
	void Reset(void);
	HRESULT MakeVertexTime(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Time();
	~Time();
};


#endif
