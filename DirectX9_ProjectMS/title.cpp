//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "title.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* タイトルで必要なインクルード */
#include "object.h"
#include "light.h"
#include "player.h"
#include "skydome.h"
#include "cube.h"
#include "stage.h"
#include "titlelogo.h"
#include "particle.h"
#include "joycon.h"
#include "fade.h"
#include "scene.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 更新処理
//=============================================================================
void TitleScene::Update(void)
{
	ObjectManager::UpdateAll();
	SceneChange();
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleScene::Draw(void)
{
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawAll();
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
TitleScene::TitleScene(void)
{
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<Titlelogo>();

	
}
//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
TitleScene::~TitleScene(void)
{
	ObjectManager::ReleaseAll();

}

//=============================================================================
// シーンチェンジの確認
//=============================================================================
void TitleScene::SceneChange(void)
{
	if (!bSceneChange)
	{
		// Joyconの数だけ回す
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// 決定になりえるボタンが押されている場合、遷移フラグを true
			if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
				| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A) 
				|| GetKeyboardTrigger(DIK_RETURN))
					bSceneChange = true;
		}

		// 遷移フラグが true なら遷移開始
		if (bSceneChange) SetFadeScene(SceneManager::SELECT);
	}
}