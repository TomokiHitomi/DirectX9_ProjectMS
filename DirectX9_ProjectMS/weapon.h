//=============================================================================
//
// �E�F�|������ [weapon.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _WEAPON_H_
#define _WEAPON_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "XModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	WEAPON_SCL					(10.0f)
#define	WEAPON_SCL_VEC3				(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// �ǂݍ��ރ��f����

// �c������
#define WEAPON_TIME_MAX				(300)

// �ړ��X�s�[�h
#define WEAPON_MOVE_SPEED			(2.5f)

// ��]�X�s�[�h
#define WEAPON_ROT_SPEED			(0.2f)

// �����[�g
#define WEAPON_REMOTE_TIME			(5)		// �����[�g�J�n����
#define WEAPON_REMOTE_CORRECTION	(0.005f)		// �����x�␳
#define WEAPON_REMOTE_ADD_MAX		(0.03f)		// �P�t���[���̍ő���Z�l
#define WEAPON_REMOTE_MAX			(0.35f)		// �ő���Z�l


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Weapon
{
private:
	CXModel*		pXModel;			// ���f���i�[�p
	D3DXVECTOR3		vPos;				// ���W���
	D3DXVECTOR3		vRot;				// ��]���
	D3DXVECTOR3		vScl;				// �g�k���
	D3DXVECTOR3		vMove;				// �ړ����
	D3DXVECTOR3		vShot;
	D3DXVECTOR3		vRemote;
	D3DXMATRIX		mtxWorld;			// ���[���h�}�g���N�X
	int				nTime;				// �����J�E���g
	float			fRemote;
	float			fSize;
	float			fDamage;
	bool			bRot;
	bool			bUse;				// �g�p�t���O

public:
	Weapon(CXModel* XModel);
	virtual ~Weapon();
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetStatus(float size, float damage,float scl,bool rot);


	virtual void SetSize(float size) { fSize = size; }
	virtual float GetSize(void) { return fSize; }

	virtual void SetDamage(float damage) { fDamage = damage; }
	virtual float GetDamage(void) { return fDamage; }

	virtual void SetScl(float fScl);
	virtual void SetRot(bool bUse);
	virtual bool Set(D3DXVECTOR3 pos, D3DXVECTOR3 shot);


	virtual void SetUse(bool use) { bUse = use; }
	virtual bool GetUse(void) { return bUse; }
	virtual void Remote(float remote);
	virtual D3DXVECTOR3 GetPos(void) { return vPos; }
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
