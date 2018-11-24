//=============================================================================
//
// �Q�[������ [select.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "select.h"

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
#include "selectface.h"
#include "particle.h"

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
void SelectScene::Update(void)
{
	ObjectManager::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void SelectScene::Draw(void)
{
	////for (unsigned int i = 0; i < 2; i++)
	////{
	//CameraManager::Set(CameraManager::SINGLE);
	//ObjectManager::DrawAll();
	////}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
SelectScene::SelectScene(void)
{
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<Selectface>();
	

}

//=============================================================================
// �f�X�g���N�^�����i�I���j
//=============================================================================
SelectScene::~SelectScene(void)
{
	ObjectManager::ReleaseAll();
}