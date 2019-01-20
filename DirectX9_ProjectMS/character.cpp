//=============================================================================
//
// �L�����N�^�[���� [character.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "character.h"
#include "player.h"

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
		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] = new CSkinMesh;
		}
	}

	if (CharacterManager::m_bUse)
	{
		m_CSkinMesh[FIREMAN]->Init(pDevice, CHARACTER_FIREMAN);
		m_CSkinMesh[DOCTOR]->Init(pDevice, CHARACTER_DOCTOR);
		m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
		m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);

		//m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
		//m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);
	}

	// ���[�v���Ȃ��A�j���[�V�������w��
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
		{
			m_CSkinMesh[i]->LoopAnim(Player::JUMP_START, false, j);

			m_CSkinMesh[i]->LoopAnim(Player::ATK_LEFT, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_RIGHT, false, j);

			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP1, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP2, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP3, false, j);
		}
	}
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
	if (CharacterManager::m_bUse)
	{
		return m_CSkinMesh[etype];
	}
	else
	{
		return NULL;
	}

}