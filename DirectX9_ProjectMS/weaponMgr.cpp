//=============================================================================
//
// �E�F�|���}�l�[�W���[���� [weaponMgr.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "weapon.h"
#include "weaponMgr.h"
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
int			WeaponManager::nCount;
Weapon*		WeaponManager::pWeapon[(int)MAX * (int)PlayerManager::PLAYER_MAX];

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
WeaponManager::WeaponManager(void)
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::WEAPON, Priority::Middle, Priority::Middle);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	nCount = (int)MAX * (int)PlayerManager::PLAYER_MAX;

	for (unsigned int i = 0; i < nCount; i++)
	{
		pWeapon[i] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
WeaponManager::~WeaponManager(void)
{
	for (unsigned int i = 0; i < nCount; i++)
	{
		SAFE_DELETE(pWeapon[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void WeaponManager::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("�y Weapon �z\n");
#endif
	for (unsigned int i = 0; i < nCount; i++)
	{
		//SAFE_UPDATE(pWeapon[i]);
		if (pWeapon[i] != NULL)
		{
			pWeapon[i]->Update();
		}
	}
#ifdef _DEBUG
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void WeaponManager::Draw(void)
{
	for (unsigned int i = 0; i < nCount; i++)
	{
		//SAFE_DRAW(pWeapon[i]);
		if (pWeapon[i] != NULL)
		{
			pWeapon[i]->Draw();
		}
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
Weapon *WeaponManager::SetWeapon(int nPlayer, WeaponManager::WeaponType eType)
{
	pWeapon[nPlayer * 2 + (int)eType] = new Weapon;
	return pWeapon[nPlayer * 2 + (int)eType];
}