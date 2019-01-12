//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "game.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* ゲームで必要なインクルード */
#include "fade.h"
#include "skydome.h"
#include "stage.h"
#include "player.h"
#include "effect.h"
#include "particle.h"
#include "time.h"
#include "rightleft.h"
#include "ko.h"
#include "roundlogo.h"
#include "timeuplogo.h"
#include "gage.h"
#include "gage3d.h"
#include "gray.h"
#include "grayko.h"
#include "weaponMgr.h"
#include "collision.h"
#include "resultselect.h"
#include "joycon.h"
#include "scene.h"
#include "time.h"

/* デバッグ */
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
bool	GameScene::m_bGame = false;
int		GameScene::m_nGameRound = 0;
int		GameScene::m_nRoundWin = 0;

//=============================================================================
// 更新処理
//=============================================================================
void GameScene::Update(void)
{
	if (!m_bGame)
	{
		if (m_nGameCount == GAME_ROUND_START)
		{
			if (bSceneChange) SetFadeScene(SceneManager::RESULT);
			else
			{
				if (Ko::GetUse())
				{
					ObjectManager::GetObjectPointer<Ko>(ObjectManager::KO)->Unset();
				}
				Time* pTime = ObjectManager::GetObjectPointer<Time>(ObjectManager::TIME);
				pTime->Reset();
				pTime->SetStart(false);

				PlayerManager::Reset();

				Roundlogo* pRoundlogo = ObjectManager::GetObjectPointer<Roundlogo>(ObjectManager::ROUNDLOGO);
				pRoundlogo->Set(m_nGameRound);
			}
		}
		if (m_nGameCount > GAME_ROUND_START)
		{
			if (!bSceneChange)
			{
				Roundlogo* pRoundlogo = ObjectManager::GetObjectPointer<Roundlogo>(ObjectManager::ROUNDLOGO);
				if (!pRoundlogo->GetUse()) 
				{ 
					m_bGame = true;
					m_nGameCount = 0;
					ObjectManager::GetObjectPointer<Time>(ObjectManager::TIME)->SetStart(true);
				}
			}
		}
		// ゲームカウントをインクリメント
		m_nGameCount++;
	}



	// リザルトセレクトのポインタを取得
	Resultselect* pResultselect = ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT);

	// グレーのポインタを取得
	Gray* pGray = ObjectManager::GetObjectPointer<Gray>(ObjectManager::GRAY);

	// ポーズフラグが false ならば
	if (!bPause)
	{
		// 全てUpdateする
		ObjectManager::UpdateAll();
	}
	else
	{
		// リザルトセレクトだけUpdateする
		pResultselect->Update();
	}

	if (m_bGame)
	{
		if (ObjectManager::GetObjectPointer<Time>(ObjectManager::TIME)->GetEnd())
		{
			float fHp = 0.0f;
			int nIdx = 0;
			Player* pPlayer;
			for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
			{
				pPlayer = PlayerManager::GetPlayer((PlayerManager::PLAYER)i);
				if (pPlayer->GetHp() >= fHp)
				{
					fHp = pPlayer->GetHp();
					nIdx = pPlayer->m_nNum;
				}
				pPlayer->ChangeAnimSpeed(PLAYER_ANIM_SPEED_DEF);
				pPlayer->ChangeAnim(Player::IDOL, PLAYER_ANIM_WEIGHT_DAMAGE);
			}
			// 勝利プレイヤーを設定
			GameScene::SetRoundWin(pPlayer->m_nNum);
		}

		// ポーズ情報を取得
		Pause();

		pGray->GrayObj[0].Use = bPause;
		pResultselect->s_bUse = bPause;
		// リザルトセレクトの使用フラグをポーズフラグと同期
		for (int i = 0; i < NUM_RESULTSELECT; i++)
		{
			pResultselect->ResultselectObj[i].Use = bPause;
		}

		// 当たり判定
		ChackHit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void GameScene::Draw(void)
{
	// デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	//{
	//	CameraManager::Set(CameraManager::CameraType(i));
	//	ObjectManager::DrawAll();
	//	//pDevice->Present(NULL, NULL, NULL, NULL);
	//}
	//CameraManager::Set(CameraManager::SINGLE);

	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		CameraManager::Set(CameraManager::CameraType(i));
		ObjectManager::DrawNormalAll();
		//pDevice->Present(NULL, NULL, NULL, NULL);
	}
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawUiAll();
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
GameScene::GameScene(void)
{
	m_bGame = false;
	m_nGameCount = 0;
	m_nGameRound = 0;
	m_nRoundWin = 0;
	//new Copyright;
	//new AirWaterFream;
	//ObjectManager::CreateObject<Skydome>();
	//ObjectManager::CreateObject<Cube>();
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<WeaponManager>();
	ObjectManager::CreateObject<PlayerManager>();
	ObjectManager::CreateObject<EffectManager>();
	ObjectManager::CreateObject<Roundlogo>();
	ObjectManager::CreateObject<Rightleft>();
	ObjectManager::CreateObject<Gage>();
	ObjectManager::CreateObject<Gage3d>();
	ObjectManager::CreateObject<Gray>();
	ObjectManager::CreateObject<Grayko>();
	ObjectManager::CreateObject<Timeuplogo>();
	ObjectManager::CreateObject<Ko>();
	ObjectManager::CreateObject<Time>();
	ObjectManager::CreateObject<Resultselect>();
	//new Player;
	//new Skydome;
	//new Cube;
	//new Stencil;

	//// 指定オブジェクト取得テスト
	//Object *pTest1 = Object::GetObjectPointer(Object::PLAYER);
	//Object *pTest2 = Object::GetObjectPointer(Object::COPYRIGHT);
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
GameScene::~GameScene(void)
{
	ObjectManager::ReleaseAll();
}

//=============================================================================
// ラウンドの勝利プレイヤーを格納
//=============================================================================
void GameScene::SetRoundWin(int num)
{
	ObjectManager::GetObjectPointer<Time>(ObjectManager::TIME)->SetStart(false);
	ObjectManager::GetObjectPointer<Ko>(ObjectManager::KO)->Set(num);
	m_nRoundWin += num;
	if (m_nGameRound == 1)
	{
		if (m_nRoundWin == 0) { SceneManager::SetWinPlayer((int)GP1); bSceneChange = true; }
		if (m_nRoundWin == 2) { SceneManager::SetWinPlayer((int)GP2); bSceneChange = true; }
	}
	else if (m_nGameRound == 2)
	{
		if (m_nRoundWin == 1) { SceneManager::SetWinPlayer((int)GP1); bSceneChange = true; }
		if (m_nRoundWin == 2) { SceneManager::SetWinPlayer((int)GP2); bSceneChange = true; }
	}

	m_nGameRound++;
	m_bGame = false;
}


//=============================================================================
// ポーズの確認
//=============================================================================
void GameScene::Pause(void)
{
	// ポーズになりえるボタンが押されている場合、遷移フラグを true
	if (GetKeyboardTrigger(DIK_ESCAPE))
	{
		SetSe(SE_CANCEL, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
		bPause = bPause ? false : true;
	}
	else
	{
		// Joyconの数だけ回す
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// ポーズになりえるボタンが押されている場合、遷移フラグを true
			if (JcTriggered(i, JC_L_BUTTON_MINUS | JC_R_BUTTON_PLUS)
				|| GetKeyboardTrigger(DIK_ESCAPE))
			{
				SetSe(SE_CANCEL, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
				bPause = bPause ? false : true;;
			}
		}
	}
}

//=============================================================================
// シーンチェンジの確認
//=============================================================================
//void GameScene::SceneChange(void)
//{
//	if (BaseScene::bSceneChange)
//	{
//		// Joyconの数だけ回す
//		for (unsigned int i = 0; i < GetJoyconSize(); i++)
//		{
//			// 決定になりえるボタンが押されている場合、遷移フラグを true
//			if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
//				| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
//				|| GetKeyboardTrigger(DIK_RETURN))
//				bSceneChange = true;
//		}
//
//		// 遷移フラグが true なら遷移開始
//		if (bSceneChange) SetFadeScene(SceneManager::SELECT);
//	}
//}