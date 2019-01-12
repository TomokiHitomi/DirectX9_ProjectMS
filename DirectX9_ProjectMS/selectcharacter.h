//=============================================================================
//
// �Z���N�g�L�����N�^�[���� [selectcharacter.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _SELECTCHARACTER_H_
#define _SELECTCHARACTER_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "character.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECTCHARCTER_POS_MARGIN	(30.0f)
#define SELECTCHARCTER_CAMERA_EYE	(D3DXVECTOR3(0.0f, 10.0f, 0.0f))
#define SELECTCHARCTER_CAMERA_AT1	(D3DXVECTOR3(-10.0f, 5.0f, -15.0f))
#define SELECTCHARCTER_CAMERA_AT2	(D3DXVECTOR3(10.0f, 5.0f, -15.0f))

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SelectCharacterManager : public ObjectManager
{
public:

	CSkinMesh	*m_CSkinMesh[CharacterManager::TYPE_MAX];	// �X�L�����b�V���i�[�p
	D3DXVECTOR3	vPos[CharacterManager::TYPE_MAX];
	D3DXVECTOR3	vScl[CharacterManager::TYPE_MAX];
	D3DXVECTOR3	vRot[CharacterManager::TYPE_MAX];
	D3DXMATRIX mtxWorld[CharacterManager::TYPE_MAX];


public:
	// �R���X�g���N�^�i�����������j
	SelectCharacterManager(void);
	//�f�X�g���N�^�i�I�������j
	~SelectCharacterManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	static bool m_bUse;

private:
	D3DXVECTOR3 SetScl(float scl) { return D3DXVECTOR3(scl, scl, scl); }
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
