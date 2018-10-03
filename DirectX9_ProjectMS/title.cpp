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
#include "SkinMeshX.h"
#include "light.h"
#include "player.h"
#include "skydome.h"
#include "cube.h"
#include "stage.h"

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
	pEffect->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleScene::Draw(void)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		Camera::Set(i);			// �J����
		ObjectManager::DrawAll();
		pEffect->Draw();
	}
}

//=============================================================================
// �R���X�g���N�^�����i�������j
//=============================================================================
TitleScene::TitleScene(void)
{
	//new Copyright;
	//new AirWaterFream;
	//ObjectManager::CreateObject<Player>();
	ObjectManager::CreateObject<Skydome>();
	//ObjectManager::CreateObject<Cube>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<PlayerManager>();
	//new Player;
	//new Skydome;
	//new Cube;
	//new Stencil;

	pEffect = new Effect;
	//// �w��I�u�W�F�N�g�擾�e�X�g
	//Object *pTest1 = Object::GetObjectPointer(Object::PLAYER);
	//Object *pTest2 = Object::GetObjectPointer(Object::COPYRIGHT);
}

//=============================================================================
// �f�X�g���N�^�����i�I���j
//=============================================================================
TitleScene::~TitleScene(void)
{
	ObjectManager::ReleaseAll();
	if (pEffect != NULL)
	{
		delete pEffect;
	}

}

//=============================================================================
// �^�C�g���f���̃��X�^�[�g���\�b�h
//=============================================================================
void TitleScene::DemoRestart(void)
{

}