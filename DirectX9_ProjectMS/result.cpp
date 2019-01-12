//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "result.h"

/* �S�̂ŕK�v�ȃC���N���[�h */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* ���U���g�ŕK�v�ȃC���N���[�h */
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
			// Joycon�̐�������
			for (unsigned int i = 0; i < GetJoyconSize(); i++)
			{
				// ����ɂȂ肦��{�^����������Ă���ꍇ�A�J�ڃt���O�� true
				if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
					| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
					|| GetKeyboardTrigger(DIK_RETURN))m_bUse = true;
			}
		}
		if (m_bUse)
		{
			ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT)->Set(true);
			// �O���[�̃|�C���^���擾
			ObjectManager::GetObjectPointer<Gray>(ObjectManager::GRAY)->GrayObj[0].Use = true;

		}
	}
	//if (m_nCount > RESULT_SELECT)
	//{
	//	//if (m_bUse)
	//	//{
	//		// ���U���g�Z���N�g�̃|�C���^���擾
	//		Resultselect* pResultselect = ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT);
	//		// ���U���g�Z���N�g�̎g�p�t���O���|�[�Y�t���O�Ɠ���
	//	//}
	//}
	m_nCount++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultScene::Draw(void)
{
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawAll();
}

//=============================================================================
// �R���X�g���N�^�����i�������j
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
// �f�X�g���N�^�����i�I���j
//=============================================================================
ResultScene::~ResultScene(void)
{
	ObjectManager::ReleaseAll();
}
