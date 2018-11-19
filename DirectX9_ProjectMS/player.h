//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "object.h"
#include "SkinMeshX.h"
#include "XModel.h"
#include "XTexture.h"
#include "character.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define PLAYER_MODEL				("flower.X")
//#define PLAYER_MODEL				("data/MODEL/Yuko.x")
//#define PLAYER_MODEL_FIREMAN		("data/MODEL/hackadollMMD.x")
//#define PLAYER_MODEL_DOCTOR			("data/MODEL/Yuko.x")

#define PLAYER_POS					(D3DXVECTOR3(0.0f,0.0f,-20.0f))

//#define PLAYER_MODEL_BONE_WING		("No_9_joint_Torso2")
//#define PLAYER_MODEL_BONE_RM		("No_45_joint_RightMiddle2")

// ���f���X�P�[��
#define PLAYER_SCL					(0.3f)

#define PLAYER_MOVE_SPEED			(1.0f)

#define PLAYER_ALPHA_TEST			(10)


// �e�X�g�p
#define PLAYER_MARGIN_MOVE			(0.02f)
#define PLAYER_MARGIN_GUARD			(0.3f)
#define PLAYER_MARGIN_ATTACK		(1.1f)

#define PLAYER_MOVE_INERTIA			(0.3f)

// �A�^�b�N


// �W�����v
#define PLAYER_GRAVITY				(0.3f)
#define PLAYER_VELOCITY				(5.0f)

// �_�b�V��
#define PLAYER_DASH					(5.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Player
{
public:
	CSkinMesh		*m_CSkinMesh;	// �X�L�����b�V���i�[�p

	// �R���X�g���N�^�i�����������j
	Player(void);
	//�f�X�g���N�^�i�I�������j
	~Player(void);

	// �X�V����
	void	Update(void);
	void	LateUpdate(void);
	// �`�揈��
	void	Draw(void);

	int				m_nNum;				// �v���C���[�i���o�[
	int				m_nTagNum;
	bool			m_bUse;				// �g�p�t���O
private:
	struct 
	D3DXVECTOR3		m_vPos;				// ���W���
	D3DXVECTOR3		m_vRot;				// ��]���
	D3DXVECTOR3		m_vScl;				// �g�k���
	D3DXVECTOR3		m_vMove;			// �ړ��ʏ��
	D3DXVECTOR3		m_vRotInertia;		// ��]���
	D3DXVECTOR3		m_vRotDiff;			// ��]����
	D3DXVECTOR3		m_vRotDistance;		// ��]����
	D3DXVECTOR3		m_vRotDest;			// ��]�ړI�n
	D3DXVECTOR3		m_vUp;

	D3DXVECTOR3		m_vTag;				// �^�[�Q�b�g���W

	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���N�X

	int				m_nCount;			// �ėp�J�E���^�[
	int				m_nCoolDown;
	float			m_fMoveSpeed;
	float			m_fMoveInertia;
	float			m_fMoveAccel;
	float			m_fRiseSpeed;


	void	Move(void);
	void	Dash(void);
	//void	Guard(void);
	//void	Action(void);
	void	Jump(void);
	void	MoveFunc(float);
	void	MoveInertia(float fInertia);
	void	RotFunc(D3DXVECTOR3);
	void	SetNum(int nNum) { m_nNum = nNum; }

	// �W�����v�p
	float	fVelocity;				// �����x
	float	fGravity;				// �d��
	bool	bJump;					// �W�����v�t���O

	// �_�b�V���p
	D3DXVECTOR3		vDash;			// �ړ��ʏ��
	int				nDashCount;
	bool			bDash;

public:
	void SetTag(D3DXVECTOR3 vTag) { m_vTag = vTag; }
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }

	void SetPlayerAnime(DWORD dwAnime, FLOAT fShift);

	// �ǋL�͋t���i�V�������̂���i�[�����j
	enum PLAYER_ANIME
	{	// �A�j���[�V����
		PLAYER_ANIME_HOSTAGE,	// �����i�ҋ@�j
		PLAYER_ANIME_RUN2,		// �����i�����j
		PLAYER_ANIME_CRYING,	// ����
		PLAYER_ANIME_CHEERING,	// ����
		PLAYER_ANIME_DIG,		// �z���i���E�ҋ@�j
		PLAYER_ANIME_SNEAKING,	// �z���i���E�����j
		PLAYER_ANIME_HANGING,	// �z���i���j
		PLAYER_ANIME_ANGRY,		// �ҋ@�i���j
		PLAYER_ANIME_HAPPY,		// �ҋ@�i���j
		PLAYER_ANIME_RUN,		// ����
		PLAYER_ANIME_MAX		// �A�j���[�W������
	};
};

class PlayerManager : public ObjectManager
{
public:
	enum PLAYER
	{	// �v���C���[�Ǘ�
		PLAYER_1P,
		PLAYER_2P,
		PLAYER_MAX
	};
	Player		*m_pPlayer[PLAYER_MAX];

public:
	// �R���X�g���N�^�i�����������j
	PlayerManager(void);
	//�f�X�g���N�^�i�I�������j
	~PlayerManager(void);

	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);

	template <class Type>
	void Set(PLAYER player, CharacterManager::TYPE type)
	{
		delete m_pPlayer[player];
		m_pPlayer[player] = new Type;
		m_pPlayer[player]->m_nNum = int(player);
		m_pPlayer[player]->m_nTagNum = int(PLAYER_2P - player);
		m_pPlayer[player]->m_CSkinMesh = SceneManager::GetCharMgr()->GetCharData(type);
		if (m_pPlayer[player]->m_CSkinMesh)
		{
			m_pPlayer[player]->m_CSkinMesh->ChangeAnim(Player::PLAYER_ANIME_HOSTAGE, 0.05f);
		}	
	}
	//void ReleaseStage(void)
	//{
	//	if (m_pStage != NULL)
	//	{
	//		delete m_pStage;
	//	}
	//}

	Player *GetPlayer(PLAYER player) { return m_pPlayer[player]; }

private:
	void SetTag(void);
};

class Fireman : public Player
{
public:
	Fireman() : Player()
	{
		// ���f���̏�����
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN, 0.05f);
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN);
	}
	~Fireman();

};

class Doctor : public Player
{
public:
	Doctor() : Player()
	{
		// ���f���̏�����
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN, 0.05f);
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN);
	}
	~Doctor()
	{

	}
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
