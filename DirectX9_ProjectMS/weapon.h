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
//// ���f��
#define	WEAPON_MODEL_TEST	"data/MODEL/Weapon/�A���Ċ�.x"	// �ǂݍ��ރ��f����
//#define	WEAPON_MODEL_TEST	"data/MODEL/cube.x"	// �ǂݍ��ރ��f����

//#define	WEAPON_TEXTURE_TEST	"data/TEXTURE/white_1x1.png"	// �ǂݍ��ރ��f����

#define	WEAPON_SCL			(18.0f)			// �ǂݍ��ރ��f����
#define	WEAPON_SCL_VEC3		(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// �ǂݍ��ރ��f����

#define WEAPON_TIME_MAX		(120)

#define WEAPON_MOVE_SPEED	(3.0f)
#define WEAPON_HEIGHT		(7.0f)


//// ���f���̍ő吔
//#define MODEL_STAGE_MAX			(1)
//
//// ���f���X�P�[��
//#define MODEL_STAGE_SCL			(30.0f)

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
	bool			bUse;				// �g�p�t���O

public:
	Weapon(CXModel* XModel);
	virtual ~Weapon();
	virtual void Update(void);
	virtual void Draw(void);
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
