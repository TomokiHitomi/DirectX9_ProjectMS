//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "result.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* リザルトで必要なインクルード */
#include "skydome.h"
#include "particle.h"
#include "gray.h"
#include "resultselect.h"
#include "winnerlogo.h"
#include "joycon.h"
#include "resultcharacter.h"

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
extern SceneManager		g_cScene;				// Sceneマネージャ

//=============================================================================
// 更新処理
//=============================================================================
void ResultScene::Update(void)
{
	ObjectManager::UpdateAll();

	if (m_nCount == RESULT_WINNER)
	{
		ObjectManager::GetObjectPointer<Winnerlogo>(ObjectManager::WINNERLOGO)->Set();
	}
	else if (m_nCount > RESULT_WINNER)
	{
		if (GetKeyboardTrigger(DIK_RETURN)) m_bUse = true;
		else
		{
			// Joyconの数だけ回す
			for (unsigned int i = 0; i < GetJoyconSize(); i++)
			{
				// 決定になりえるボタンが押されている場合、遷移フラグを true
				if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
					| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
					|| GetKeyboardTrigger(DIK_RETURN))m_bUse = true;
			}
		}
		if (m_bUse)
		{
			ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT)->Set(true);
			// グレーのポインタを取得
			ObjectManager::GetObjectPointer<Gray>(ObjectManager::GRAY)->GrayObj[0].Use = true;

		}
	}
	//if (m_nCount > RESULT_SELECT)
	//{
	//	//if (m_bUse)
	//	//{
	//		// リザルトセレクトのポインタを取得
	//		Resultselect* pResultselect = ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT);
	//		// リザルトセレクトの使用フラグをポーズフラグと同期
	//	//}
	//}
	m_nCount++;
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultScene::Draw(void)
{
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawAll();
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
ResultScene::ResultScene(void)
{
	m_nCount = 0;
	m_bUse = false;
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<Winnerlogo>();
	ObjectManager::CreateObject<Gray>();
	ObjectManager::CreateObject<Resultselect>();
	ObjectManager::CreateObject<ResultCharacterManager>();
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
ResultScene::~ResultScene(void)
{
	ObjectManager::ReleaseAll();
}
