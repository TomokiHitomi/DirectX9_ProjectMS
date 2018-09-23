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

//*****************************************************************************
// マクロ定義
//*****************************************************************************

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