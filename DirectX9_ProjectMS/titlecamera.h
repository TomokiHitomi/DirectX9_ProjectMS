//=============================================================================
//
// プレイヤー処理 [ko.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _TITLECAMERA_H_
#define _TITLECAMERA_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================



#define TEXTURE_TITLECAMERA_SCOND						(3)																// テクスチャ頂点カラー変化前
#define TEXTURE_TITLECAMERA_SCOND_COUNT				(2)
#define TEXTURE_TITLECAMERA_SCOND_COUNT_COLOR			(255.0f /TEXTURE_TITLECAMERA_SCOND_COUNT)
#define TEXTURE_TITLECAMERA_SCOND_TIME				(FRAME*TEXTURE_TITLECAMERA_SCOND)									//300
#define TEXTURE_TITLECAMERA_SCOND_COLOR				(TEXTURE_TITLECAMERA_SCOND_COUNT_COLOR/TEXTURE_TITLECAMERA_SCOND_TIME)								//90
#define TITLECAMERA_LENGTH							(125.0f)
#define NUM_TITLECAMERA								(1)																// テクスチャの数
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Titlecamera : public ObjectManager
{
public:


	struct TitlecameraParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		float					Color;
		bool					Use;									// true:使用  false:未使用
		bool					Nowselect;
	};
	TitlecameraParts TitlecameraObj[NUM_TITLECAMERA];
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlecamera();
	~Titlecamera();
};


#endif
