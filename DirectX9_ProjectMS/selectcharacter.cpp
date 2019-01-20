//=============================================================================
//
// �Z���N�g�L�����N�^�[���� [selectcharacter.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "selectcharacter.h"
#include "selectface.h"
#include "scene.h"
#include "calculate.h"
#include "player.h"
#include "camera.h"
#include "input.h"

// �f�o�b�O�p
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
//bool CharacterManager::m_bUse = true;

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
SelectCharacterManager::SelectCharacterManager(void)
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::SELECTCHARACTER, Priority::Middle, Priority::Middle);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjectType(ObjectManager::ObjectType::NORMAL);


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		m_CSkinMesh[i] = NULL;
		vPos[i] = ZERO_D3DXVECTOR3;
		vPos[i].x = (i * SELECTCHARCTER_POS_MARGIN) - ((CharacterManager::TYPE_MAX - 1) * SELECTCHARCTER_POS_MARGIN / 2);

		vRot[i] = D3DXVECTOR3(0.0f, -0.35f, 0.0f);

		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] =
				SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)i);
			if (m_CSkinMesh[i])
			{
				m_CSkinMesh[i]->ChangeAnim(Player::IDOL, 1.0f, 0);
				m_CSkinMesh[i]->ChangeAnim(Player::IDOL, 1.0f, 1);

				//m_CSkinMesh[i]->LoopAnim(Player::IDOL, false, 0);
				//m_CSkinMesh[i]->LoopAnim(Player::IDOL, false, 1);
			}
		}
	}
	Init();
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
SelectCharacterManager::~SelectCharacterManager(void)
{
	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		//if(!m_CSkinMesh[i])
		//delete m_CSkinMesh[i];
		m_CSkinMesh[i] = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
void SelectCharacterManager::Init(void)
{
	// �e���f���̃X�P�[����ݒ�
	vScl[CharacterManager::FIREMAN] = SetScl(CHARACTER_FIREMAN_SCL);
	vScl[CharacterManager::PASTRY] = SetScl(CHARACTER_PASTRY_SCL);
	vScl[CharacterManager::IDOL] = SetScl(CHARACTER_IDOL_SCL);
	vScl[CharacterManager::DOCTOR] = SetScl(CHARACTER_DOCTOR_SCL);

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		WorldConvert(&mtxWorld[i], vPos[i], vRot[i], vScl[i]);
	}

	// �J����������ݒ�
	Camera* pCamera;
	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		pCamera = CameraManager::GetCamera((CameraManager::CameraType)i);
		pCamera->SetAtIner(0.3f);
		pCamera->SetEyeIner(0.1f);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void SelectCharacterManager::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("�y�@SelectCharacter�@�z\n");
#endif



	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_LEFT))vRot[i].y += 0.1f;
		if (GetKeyboardTrigger(DIK_RIGHT))vRot[i].y -= 0.1f;
		PrintDebugProc("rot[%f] \n", vRot[i].y);
#endif
		WorldConvert(&mtxWorld[i], vPos[i], vRot[i], vScl[i]);
	}

	int nSelectChar;
	for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
	{
		nSelectChar = SearchCharSelect(i);

		for (unsigned int j = 0; j < CharacterManager::TYPE_MAX; j++)
		{
			if (m_CSkinMesh[j] != NULL) m_CSkinMesh[j]->Update(i);
		}

		// �J������At���Z�b�g
		CameraManager::pCamera[i]->SetAt(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_EYE);

		// �J����Eye���Z�b�g
		if		(i == 0) CameraManager::pCamera[i]->SetEye(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_AT1);
		else if	(i == 1) CameraManager::pCamera[i]->SetEye(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_AT2);


#ifdef _DEBUG
		PrintDebugProc("Player%d:[%d] \n",i, nSelectChar);
#endif
	}



	//for (unsigned int j = 0; j < CharacterManager::TYPE_MAX; j++)
	//{



	//}
#ifdef _DEBUG
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void SelectCharacterManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCameraType = (int)CameraManager::GetType();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL)
		m_CSkinMesh[i]->Draw(pDevice, mtxWorld[i], nCameraType);
	}
}


////=============================================================================
//// �L�����N�^�[�f�[�^�̎擾����
////=============================================================================
//CSkinMesh *CharacterManager::GetCharData(CharacterManager::TYPE etype)
//{
//	if (CharacterManager::m_bUse)
//	{
//		return m_CSkinMesh[etype];
//	}
//	else
//	{
//		return NULL;
//	}
//
//}