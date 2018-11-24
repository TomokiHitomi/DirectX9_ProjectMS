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
////// ���f��
//#define	WEAPON_MODEL_TEST	"data/MODEL/cube.x"	// �ǂݍ��ރ��f����
//#define	WEAPON_TEXTURE_TEST	"data/TEXTURE/white_1x1.png"	// �ǂݍ��ރ��f����
//
//#define	WEAPON_SCL			(1.0f)			// �ǂݍ��ރ��f����
//#define	WEAPON_SCL_VEC3		(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// �ǂݍ��ރ��f����
//
//#define WEAPON_TIME_MAX		(120)
//
//#define WEAPON_MOVE_SPEED	(5)

#define	WEAPON_MODEL_BEATER	"data/MODEL/Weapon/�A���Ċ�.x"	// �ǂݍ��ރ��f����
#define	WEAPON_MODEL_BOWL	"data/MODEL/Weapon/�{�E��.x"	// �ǂݍ��ރ��f����

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
