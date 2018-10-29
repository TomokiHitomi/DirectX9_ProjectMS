//=============================================================================
//
// タイトル処理 [title.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TITLE_SELECT00				"data/TEXTURE/logo000.png"											// ロゴ
#define TEXTURE_TITLE_SIZE000_LATE			(2.0)																// 拡大倍率
#define TEXTURE_TITLE_SIZE000_X				(TEXTURE_TITLE_SIZE000_LATE*SCREEN_WIDTH/SCREEN_WIDTH)					// サイズ
#define TEXTURE_TITLE_SIZE000_Y				(TEXTURE_TITLE_SIZE000_LATE*SCREEN_HEIGHT/SCREEN_HEIGHT)				// サイズ
#define tEXTURE_TITLE_POSITION000X			(SCREEN_WIDTH/2)
#define tEXTURE_TITLE_POSITION000_Y			(SCREEN_HEIGHT/2)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TitleScene :public BaseScene
{   // :public  BaseScene
public:
	TitleScene(void);
	~TitleScene(void);
	void Update(void);
	void Draw(void);
private:
	void DemoRestart(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif