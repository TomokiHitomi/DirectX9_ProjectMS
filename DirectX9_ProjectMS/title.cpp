//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "title.h"

/* �S�̂ŕK�v�ȃC���N���[�h */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* �^�C�g���ŕK�v�ȃC���N���[�h */
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �X�V����
//=============================================================================
void TitleScene::Update(void)
{
	ObjectManager::UpdateAll();
	SceneChange();
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleScene::Draw(void)
{
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawAll();
}

//=============================================================================
// �R���X�g���N�^�����i�������j
//=============================================================================
TitleScene::TitleScene(void)
{
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<Titlelogo>();

	
}
//=============================================================================
// �f�X�g���N�^�����i�I���j
//=============================================================================
TitleScene::~TitleScene(void)
{
	ObjectManager::ReleaseAll();

}

//=============================================================================
// �V�[���`�F���W�̊m�F
//=============================================================================
void TitleScene::SceneChange(void)
{
	if (!bSceneChange)
	{
		// Joycon�̐�������
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// ����ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
			if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
				| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A) 
				|| GetKeyboardTrigger(DIK_RETURN))
					bSceneChange = true;
		}

		// �J�ڃt���O�� true �Ȃ�J�ڊJ�n
		if (bSceneChange) SetFadeScene(SceneManager::SELECT);
	}
}