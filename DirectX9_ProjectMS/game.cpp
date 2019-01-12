//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "game.h"

/* �S�̂ŕK�v�ȃC���N���[�h */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* �Q�[���ŕK�v�ȃC���N���[�h */
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

/* �f�o�b�O */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool	GameScene::m_bGame = false;
int		GameScene::m_nGameRound = 0;
int		GameScene::m_nRoundWin = 0;

//=============================================================================
// �X�V����
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
		// �Q�[���J�E���g���C���N�������g
		m_nGameCount++;
	}



	// ���U���g�Z���N�g�̃|�C���^���擾
	Resultselect* pResultselect = ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT);

	// �O���[�̃|�C���^���擾
	Gray* pGray = ObjectManager::GetObjectPointer<Gray>(ObjectManager::GRAY);

	// �|�[�Y�t���O�� false �Ȃ��
	if (!bPause)
	{
		// �S��Update����
		ObjectManager::UpdateAll();
	}
	else
	{
		// ���U���g�Z���N�g����Update����
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
			// �����v���C���[��ݒ�
			GameScene::SetRoundWin(pPlayer->m_nNum);
		}

		// �|�[�Y�����擾
		Pause();

		pGray->GrayObj[0].Use = bPause;
		pResultselect->s_bUse = bPause;
		// ���U���g�Z���N�g�̎g�p�t���O���|�[�Y�t���O�Ɠ���
		for (int i = 0; i < NUM_RESULTSELECT; i++)
		{
			pResultselect->ResultselectObj[i].Use = bPause;
		}

		// �����蔻��
		ChackHit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameScene::Draw(void)
{
	// �f�o�C�X�̎擾
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
// �R���X�g���N�^�����i�������j
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

	//// �w��I�u�W�F�N�g�擾�e�X�g
	//Object *pTest1 = Object::GetObjectPointer(Object::PLAYER);
	//Object *pTest2 = Object::GetObjectPointer(Object::COPYRIGHT);
}

//=============================================================================
// �f�X�g���N�^�����i�I���j
//=============================================================================
GameScene::~GameScene(void)
{
	ObjectManager::ReleaseAll();
}

//=============================================================================
// ���E���h�̏����v���C���[���i�[
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
// �|�[�Y�̊m�F
//=============================================================================
void GameScene::Pause(void)
{
	// �|�[�Y�ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
	if (GetKeyboardTrigger(DIK_ESCAPE))
	{
		SetSe(SE_CANCEL, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
		bPause = bPause ? false : true;
	}
	else
	{
		// Joycon�̐�������
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// �|�[�Y�ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
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
// �V�[���`�F���W�̊m�F
//=============================================================================
//void GameScene::SceneChange(void)
//{
//	if (BaseScene::bSceneChange)
//	{
//		// Joycon�̐�������
//		for (unsigned int i = 0; i < GetJoyconSize(); i++)
//		{
//			// ����ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
//			if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
//				| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
//				|| GetKeyboardTrigger(DIK_RETURN))
//				bSceneChange = true;
//		}
//
//		// �J�ڃt���O�� true �Ȃ�J�ڊJ�n
//		if (bSceneChange) SetFadeScene(SceneManager::SELECT);
//	}
//}