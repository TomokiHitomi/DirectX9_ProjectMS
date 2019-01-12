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
#define RESULTCHARCTER_POS_MARGIN	(30.0f)
#define RESULTCHARCTER_CAMERA_EYE	(D3DXVECTOR3(0.0f, 10.0f, 0.0f))
#define RESULTCHARCTER_CAMERA_AT1	(D3DXVECTOR3(-10.0f, 5.0f, -15.0f))
#define RESULTCHARCTER_CAMERA_AT2	(D3DXVECTOR3(10.0f, 5.0f, -15.0f))

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultCharacterManager : public ObjectManager
{
private:
	enum
	{
		RESULT_WIN,
		RESULT_LOSE,
		RESULT_MAX
	};
	CSkinMesh	*m_CSkinMesh[RESULT_MAX];	// �X�L�����b�V���i�[�p
	D3DXVECTOR3	vPos[RESULT_MAX];
	D3DXVECTOR3	vScl[RESULT_MAX];
	D3DXVECTOR3	vRot[RESULT_MAX];
	D3DXMATRIX mtxWorld[RESULT_MAX];


public:
	// �R���X�g���N�^�i�����������j
	ResultCharacterManager(void);
	//�f�X�g���N�^�i�I�������j
	~ResultCharacterManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	float SearchScl(int nChar);
	static bool m_bUse;

private:
	D3DXVECTOR3 SetScl(float scl) { return D3DXVECTOR3(scl, scl, scl); }
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
