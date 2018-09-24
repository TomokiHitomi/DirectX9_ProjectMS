//=============================================================================
//
// �X�e�[�W���� [stage.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���f��
#define	STAGE_MODEL		"data/MODEL/Stage/Chinese/Chinese PVP Stage.x"	// �ǂݍ��ރ��f����
#define	STAGE_TEXTURE		"data/MODEL/Stage/Chinese/s.tga"	// �ǂݍ��ރ��f����

// ���f���̍ő吔
#define MODEL_STAGE_MAX			(1)

// ���f���X�P�[��
#define MODEL_STAGE_SCL			(30.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Stage
{
public:
	Object *pObj;
	//Stage();
	~Stage()
	{
		if (pObj != NULL)
		{
			delete pObj;
		}
	}
};


class StageManager : public ObjectManager
{
private:
	Stage *m_pStage = NULL;
public:
	// �R���X�g���N�^�i�����������j
	StageManager(void);
	//�f�X�g���N�^�i�I�������j
	~StageManager(void);

	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);

	template <typename Type>
	void SetStage(void)
	{
		if (m_pStage != NULL)
		{
			delete m_pStage;
		}
		m_pStage = new Type;
	}
	void ReleaseStage(void)
	{
		if (m_pStage != NULL)
		{
			delete m_pStage;
		}
	}
};

class StageChinese : public Stage
{
	enum
	{
		MAIN,
		MAX
	};
public:
	StageChinese()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		pObj = new Object(MAX);
		// �e�v���p�e�B�̏�����
		pObj->prop[MAIN].vScl = D3DXVECTOR3(MODEL_STAGE_SCL, MODEL_STAGE_SCL, MODEL_STAGE_SCL);
		pObj->prop[MAIN].CXModel->Init(pDevice, STAGE_MODEL, STAGE_TEXTURE);
	}
	//~StageChinese()
	//{

	//}
	// �X�V����
	void	Update(void) { ; }
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
