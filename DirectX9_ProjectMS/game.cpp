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
extern SceneManager		g_cScene;				// Scene�}�l�[�W��

//=============================================================================
// �X�V����
//=============================================================================
void GameScene::Update(void)
{
#ifdef _DEBUG
	Debugtimer timer;
#endif
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

	// �|�[�Y�����擾
	Pause();

	// ���U���g�Z���N�g�̎g�p�t���O���|�[�Y�t���O�Ɠ���
	for (int i = 0; i < NUM_RESULTSELECT; i++)
	{
		pGray->GrayObj[0].Use = bPause;
		pResultselect->ResultselectObj[i].Use = bPause;
	}

#ifdef _DEBUG
	PrintDebugProc("�y UpdateALL �z\n");
	PrintDebugProc("TIME:%f\n", timer.End());
#endif

#ifdef _DEBUG
	Debugtimer timer2;
#endif
	ChackHit();
#ifdef _DEBUG
	PrintDebugProc("�y COLLISION �z\n");
	PrintDebugProc("TIME:%f\n", timer2.End());
#endif

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
// �Q�[����~���\�b�h
//=============================================================================
bool GameScene::GameStop(void)
{
	return 0;
}

//=============================================================================
// �̊m�F
//=============================================================================
void GameScene::Pause(void)
{
	// ����ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
	if (GetKeyboardTrigger(DIK_ESCAPE))
		bPause = bPause ? false : true;
	else
	{
		// Joycon�̐�������
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// ����ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
			if (JcTriggered(i, JC_L_BUTTON_MINUS | JC_R_BUTTON_PLUS)
				|| GetKeyboardTrigger(DIK_ESCAPE))
				bPause = bPause ? false : true;;
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