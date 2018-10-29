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
	ObjectManager::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameScene::Draw(void)
{
	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		CameraManager::Set(CameraManager::CameraType(i));

		ObjectManager::DrawAll();
	}
	CameraManager::Set(CameraManager::SINGLE);
}

//=============================================================================
// �R���X�g���N�^�����i�������j
//=============================================================================
GameScene::GameScene(void)
{
	//new Copyright;
	//new AirWaterFream;
	ObjectManager::CreateObject<Skydome>();
	//ObjectManager::CreateObject<Cube>();
	ObjectManager::CreateObject<StageManager>();
	//ObjectManager::CreateObject<PlayerManager>();
	ObjectManager::CreateObject<EffectManager>();
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