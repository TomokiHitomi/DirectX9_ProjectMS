//=============================================================================
//
// �L�����N�^�[���� [character.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "character.h"

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
bool CharacterManager::m_bUse = true;

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
CharacterManager::CharacterManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		m_CSkinMesh[i] = NULL;
		m_CSkinMesh[i] = new CSkinMesh;
	}

	m_CSkinMesh[FIREMAN]->Init(pDevice, CHARACTER_FIREMAN);
	m_CSkinMesh[DOCTOR]->Init(pDevice, CHARACTER_DOCTOR);
	//m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
	//m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
CharacterManager::~CharacterManager(void)
{
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		if(!m_CSkinMesh[i])
		delete m_CSkinMesh[i];
		m_CSkinMesh[i] = NULL;
	}
}

//=============================================================================
// �L�����N�^�[�f�[�^�̎擾����
//=============================================================================
CSkinMesh *CharacterManager::GetCharData(CharacterManager::TYPE etype)
{
	return m_CSkinMesh[etype];
}