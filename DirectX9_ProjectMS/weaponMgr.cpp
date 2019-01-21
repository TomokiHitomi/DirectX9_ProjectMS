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
Weapon*		WeaponManager::pWeapon[WEAPON_MAX];
CXModel*	WeaponManager::pXModel[WeaponType::MAX];

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
WeaponManager::WeaponManager(void)
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::WEAPON, Priority::Middle, Priority::Middle);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		pWeapon[i] = NULL;
	}

	for (unsigned int i = 0; i < WeaponType::MAX; i++)
	{
		pXModel[i] = NULL;
		// ���f���f�[�^���C���X�^���X��
		pXModel[i] = new CXModel;
		pXModel[i]->SetLight(true);
	}

	// ���f���f�[�^��������

	// �p�e�B�V�G
	pXModel[BEATER]->Init(pDevice, WEAPON_MODEL_BEATER, NULL);
	pXModel[BOWL]->Init(pDevice, WEAPON_MODEL_BOWL, NULL);
	pXModel[CAKE]->Init(pDevice, WEAPON_MODEL_CAKE, NULL);
	// �A�C�h��
	pXModel[MIC]->Init(pDevice, WEAPON_MODEL_MIC, NULL);
	pXModel[CDCASE]->Init(pDevice, WEAPON_MODEL_CDCASE, NULL);
	pXModel[KARAAGE]->Init(pDevice, WEAPON_MODEL_KARAAGE, NULL);
	// �V���E�{�E�V
	pXModel[EXTINGUISHER]->Init(pDevice, WEAPON_MODEL_EXTINGUISHER, NULL);
	pXModel[HELMET]->Init(pDevice, WEAPON_MODEL_HELMET, NULL);
	pXModel[FIREENGIN]->Init(pDevice, WEAPON_MODEL_FIREENGIN, NULL);
	// �h�N�^�[
	pXModel[MESU]->Init(pDevice, WEAPON_MODEL_MESU, NULL);
	pXModel[SYRINGE]->Init(pDevice, WEAPON_MODEL_SYRINGE, NULL);
	pXModel[BED]->Init(pDevice, WEAPON_MODEL_BED, NULL);
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
WeaponManager::~WeaponManager(void)
{
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		SAFE_DELETE(pWeapon[i]);
	}

	for (unsigned int i = 0; i < WeaponType::MAX; i++)
	{
		SAFE_DELETE(pXModel[i]);
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
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
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
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
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
//Weapon *WeaponManager::SetWeapon(int nPlayer, WeaponManager::WeaponType eType)
//{
//	pWeapon[nPlayer * 2 + (int)eType] = new Weapon;
//	return pWeapon[nPlayer * 2 + (int)eType];
//}

Weapon *WeaponManager::SetWeapon(WeaponManager::WeaponType eType)
{
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		if (pWeapon[i] == NULL)
		{
			pWeapon[i] = new Weapon(pXModel[eType]);
			return pWeapon[i];
		}
	}
}