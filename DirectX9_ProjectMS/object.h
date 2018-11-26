//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "main.h"
#include "XModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************

// �I�u�W�F�N�g�p
class ObjectManager
{
public:
	// ���X�g���D�揇��
	enum Priority
	{
		Highest,
		High,
		Middle,
		Low,
		Lowest
	};

	// �I�u�W�F�N�gID
	enum ObjectID
	{
		NON,
		COPYRIGHT,
		PLAYER,
		EFFECT,
		SKYDOME,
		CUBE,
		STENCIL,
		STAGE,
		SELECTFACE,
		TITLELOGO,
		TITLEMESH,
		GAGE,
		GAGE3D,
		RESULTSELECT,
		GRAY,
		GRAYKO,
		PARTICLE,
		RIGHTLEFT,
		KO,
		WINNERLOGO,
		ROUNDLOGO,
		TIME,
		TIMEUPLOGO,
		WEAPON
	};

	// �I�u�W�F�N�g�^�C�v
	enum ObjectType
	{
		NORMAL,
		UI
	};

	// ���[�g�|�C���^
	enum ObjectRoot
	{
		UpdateRoot,
		DrawRoot,
		ObjectRootMax
	};

private:
	static int				nObjectCount;					// �S�I�u�W�F�N�g���̃J�E���^
	static ObjectManager	*s_pRoot[ObjectRootMax];		// ���X�g�̍X�V���[�g�|�C���^
	ObjectManager			*m_pPrev[ObjectRootMax];		// ���X�g�̑O�|�C���^
	ObjectManager			*m_pNext[ObjectRootMax];		// ���X�g�̎��|�C���^
	Priority				m_ePriority[ObjectRootMax];		// �D�揇�ʁi�T�u�j
	ObjectID				eObjectId;						// �I�u�W�F�N�g���ʗpID
	ObjectType				eObjectType;					// �I�u�W�F�N�g�^�C�v

public:
	// �R���X�g���N�^�i�����������j
	ObjectManager();
	// �f�X�g���N�^�i�I�������j
	virtual ~ObjectManager();

	// �X�V����
	virtual void Update(void) { ; }
	// �`�揈��
	virtual void Draw(void) { ; }
	// �������
	void Release(void);

	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	void SetIdAndPriority(ObjectID, Priority, Priority);
	// �I�u�W�F�N�g�̃��X�g�ǉ�����
	void InsertList(void);
	// �I�u�W�F�N�g�̃��X�g���E����
	void RemoveList(void);

	// �S�I�u�W�F�N�g�̍X�V����
	static void UpdateAll(void);
	// �S�I�u�W�F�N�g�̕`�揈��
	static void DrawAll(void);
	// �S�I�u�W�F�N�g�̉������
	static void ReleaseAll(void);

	// �ʏ�I�u�W�F�N�g�̕`�揈��
	static void DrawNormalAll(void);
	// UI�I�u�W�F�N�g�̕`�揈��
	static void DrawUiAll(void);


	// ���[�g�|�C���^�̎擾����
	static ObjectManager *GetObjectRoot(ObjectRoot eObjRoot) { return s_pRoot[eObjRoot]; }
	// ���[�g�|�C���^�̃A�h���X�擾����
	static ObjectManager **GetObjectRootAdr(ObjectRoot);

	// �l�N�X�g�|�C���^�̎擾����
	ObjectManager *GetObjectNext(ObjectRoot eObjRoot);


	// �I�u�W�F�N�gID�ݒ菈��
	void SetObjectId(ObjectID eObjId) { eObjectId = eObjId; }
	// �I�u�W�F�N�gID�擾����
	ObjectID GetObjectId(void) { return (eObjectId); }

	// �I�u�W�F�N�g�^�C�v�ݒ菈��
	void SetObjectType(ObjectType eObjType) { eObjectType = eObjType; }
	// �I�u�W�F�N�g�^�C�v�擾����
	ObjectType GetObjectType(void) { return (eObjectType); }

	// �v���C�I���e�B�ݒ菈��
	void SetPriority(ObjectRoot eObjRoot, Priority ePriority) { m_ePriority[eObjRoot] = ePriority; }
	// �v���C�I���e�B�擾����
	Priority GetPriority(ObjectRoot eObjRoot) { return (m_ePriority[eObjRoot]); }

	// �I�u�W�F�N�g�̃|�C���^�擾����
	template <typename Type>
	static Type *GetObjectPointer(ObjectID eObjId)
	{
		ObjectManager *pList = GetObjectRoot(UpdateRoot);

		while (pList != NULL)
		{
			if (eObjId == pList->GetObjectId())
			{
				// �Ώۃ|�C���^���w�肵���^�Ń_�E���L���X�g���ĕԂ�
				return dynamic_cast<Type*>(pList);
			}
			pList = pList->GetObjectNext(UpdateRoot);
		}
		return NULL;
	}

	// �I�u�W�F�N�g�̍쐬����
	template <typename Type>
	static void CreateObject(void)
	{
		new Type;
	}
};

class Object
{
public:
	int					nNum;
	struct Prop
	{
		CXModel			*CXModel;			// ���f���i�[�p
		D3DXVECTOR3		vPos;				// ���W���
		D3DXVECTOR3		vRot;				// ��]���
		D3DXVECTOR3		vScl;				// �g�k���
		D3DXMATRIX		mtxWorld;			// ���[���h�}�g���N�X
		bool			bUse;
	}*prop;
	
	// �X�V����
	virtual void Update(void) { ; }
	// �`�揈��
	void Draw(void);
	// �������
	void Delete(int num);

	// �R���X�g���N�^
	Object(void) { ; }
	Object(int num)
	{
		nNum = num;
		prop = new Prop[num];
		// �e�v���p�e�B�̏�����
		for (unsigned int i = 0; i < nNum; i++)
		{
			prop[i].vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			prop[i].vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			prop[i].vScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			prop[i].CXModel = new CXModel;
			prop[i].bUse = true;
		}
	}
	// �f�X�g���N�^
	~Object()
	{
		for (unsigned int i = 0; i < nNum; i++)
		{
			if (prop[i].CXModel != NULL)
			{
				prop[i].CXModel->Release();
				delete prop[i].CXModel;
			}
		}
		delete prop;
	}
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
