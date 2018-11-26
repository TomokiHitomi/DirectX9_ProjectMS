//=============================================================================
//
// �E�F�|���}�l�[�W���[���� [weaponMgr.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _WEAPONMGR_H_
#define _WEAPONMGR_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "object.h"
#include "weapon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	WEAPON_MODEL_BEATER				"data/MODEL/Weapon/�A���Ċ�.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_BEATER_SCL			(25.0f)

#define	WEAPON_MODEL_BOWL				"data/MODEL/Weapon/�{�E��.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_BOWL_SCL			(20.0f)

#define	WEAPON_MODEL_MIC				"mic.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_MIC_SCL			(2.0f)

#define	WEAPON_MODEL_CDCASE				"CDCase.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_CDCASE_SCL			(18.0f)

#define	WEAPON_MODEL_EXTINGUISHER		"extinguisher.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_EXTINGUISHER_SCL	(2.0f)

#define	WEAPON_MODEL_HELMET				"helmet.X"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_HELMET_SCL			(14.0f)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class WeaponManager : public ObjectManager
{
public:
	enum WeaponType
	{
		BEATER,
		BOWL,
		MIC,
		CDCASE,
		EXTINGUISHER,
		HELMET,
		MAX
	};
private:
	static Weapon*		pWeapon[4];
	static CXModel*		pXModel[WeaponType::MAX];			// ���f���i�[�p
	//static Weapon* pWeapon[WeaponType::MAX * 2];
	//Weapon *pWeapon[1];
public:
	// �R���X�g���N�^�i�����������j
	WeaponManager(void);
	//�f�X�g���N�^�i�I�������j
	~WeaponManager(void);

	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);

	//static Weapon *SetWeapon(int nPlayer, WeaponManager::WeaponType eType);
	static Weapon* SetWeapon(WeaponManager::WeaponType eType);

	//template <typename Type>
	//void SetStage(void)
	//{
	//	if (pWeapon != NULL)
	//	{
	//		delete pWeapon;
	//	}
	//	pWeapon = new Type;
	//}
	//void ReleaseStage(void)
	//{
	//	if (pWeapon != NULL)
	//	{
	//		delete pWeapon;
	//	}
	//}
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
