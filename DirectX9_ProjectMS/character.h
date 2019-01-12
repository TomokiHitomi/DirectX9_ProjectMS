//=============================================================================
//
// �L�����N�^�[���� [character.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "SkinMeshX.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHARACTER_FIREMAN			("data/MODEL/Fireman/Fireman.X")
#define CHARACTER_FIREMAN_SCL		(12.0f)

#define CHARACTER_PASTRY			("data/MODEL/Pastry/Pastry.X")
#define CHARACTER_PASTRY_SCL		(10.25f)

#define CHARACTER_IDOL				("data/MODEL/Idol/Idol.X")
#define CHARACTER_IDOL_SCL			(10.25f)

#define CHARACTER_DOCTOR			("Idol.X")
#define CHARACTER_DOCTOR_SCL		(0.25f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CharacterManager
{
public:
	enum TYPE
	{	// �v���C���[�Ǘ�
		FIREMAN,
		PASTRY,
		IDOL,
		DOCTOR,
		TYPE_MAX
	};
	CSkinMesh	*m_CSkinMesh[TYPE_MAX];	// �X�L�����b�V���i�[�p

public:
	// �R���X�g���N�^�i�����������j
	CharacterManager(void);
	//�f�X�g���N�^�i�I�������j
	~CharacterManager(void);
	CSkinMesh *GetCharData(CharacterManager::TYPE);
	static bool m_bUse;

private:
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
