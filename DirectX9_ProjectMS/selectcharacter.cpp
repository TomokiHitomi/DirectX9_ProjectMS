//=============================================================================
//
// �Z���N�g�L�����N�^�[���� [selectcharacter.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "selectcharacter.h"
#include "scene.h"
#include "calculate.h"

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
		vPos[i].x = i * SELECTCHARCTER_POS_MARGIN - SELECTCHARCTER_POS_MARGIN * 2;

		vRot[i] = ZERO_D3DXVECTOR3;

		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] =
				SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)i);
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
}

//=============================================================================
// �X�V����
//=============================================================================
void SelectCharacterManager::Update(void)
{
	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL)
		{
			m_CSkinMesh[i]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void SelectCharacterManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		m_CSkinMesh[i]->Draw(pDevice, mtxWorld[i]);
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