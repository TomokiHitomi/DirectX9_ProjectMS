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
#include "weapon.h"
#include "weaponMgr.h"

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
#define PLAYER_SCL					(0.2f)

// �ړ��X�s�[�h
#define PLAYER_MOVE_SPEED			(0.5f)

// ���e�X�g
#define PLAYER_ALPHA_TEST			(10)

/***** ����n *****/

// Joycon�̂�����
#define PLAYER_MARGIN_MOVE			(0.05f)
#define PLAYER_MARGIN_GUARD			(0.5f)
#define PLAYER_MARGIN_ATTACK		(1.1f)


#define PLAYER_MOVE_INERTIA			(0.3f)

// �X�e�[�^�X
#define PLAYER_HP_MAX				(100)

// �_���[�W
#define PLAYER_DAMAGE_NORMAL		(5.0f)
#define PLAYER_DAMAGE_THROW			(10.0f)
#define PLAYER_DAMAGE_SP			(30.0f)

// �A�^�b�N
#define PLAYER_ATTACK_CD			(30)		// �N�[���_�E��

// �K�[�h
#define PLAYER_GUARD_CD				(30)
#define PLAYER_GUARD_COUNT			(5)		// �K�[�h�X�^�[�g�J�E���g

// �W�����v
#define PLAYER_GRAVITY				(0.3f)
#define PLAYER_VELOCITY				(5.0f)

// �_�b�V��
#define PLAYER_DASH_CD				(10)
#define PLAYER_DASH					(2.0f)

// �����蔻��
#define PLAYER_SIZE_HIT				(5.0f)
#define PLAYER_SIZE_WEAPON			(1.0f)
#define PLAYER_HEIGHT_HIT			(10.0f)

/***** �A�j���[�V���� *****/

// �A�j���[�V�����t���O
#define PLAYER_ANIM_FRONT			0x00000001
#define PLAYER_ANIM_BACK			0x00000002
#define PLAYER_ANIM_LEFT			0x00000004
#define PLAYER_ANIM_RIGHT			0x00000008
#define PLAYER_ANIM_GUARD			0x00000010
#define PLAYER_ANIM_ATK_RIGHT		0x00000020
#define PLAYER_ANIM_ATK_LEFT		0x00000040
//#define PLAYER_ANIM_				0x00000080
//#define PLAYER_ANIM_				0x00000100
//#define PLAYER_ANIM_				0x00000200
//#define PLAYER_ANIM_				0x00001000
//#define PLAYER_ANIM_				0x00002000
//#define PLAYER_ANIM_				0x00004000
//#define PLAYER_ANIM_				0x00008000

// �A�j���[�V�����X�s�[�h
#define PLAYER_ANIM_SPEED_DEF		(60.0f / 3000.0f)
#define PLAYER_ANIM_SPEED_DASH		(60.0f / 1000.0f)

#define PLAYER_ANIM_WEIGHT_DEF		(0.1f)
#define PLAYER_ANIM_WEIGHT_ATTACK	(0.3f)
#define PLAYER_ANIM_WEIGHT_GUARD	(0.3f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Player
{
public:
	CSkinMesh*		m_CSkinMesh;	// �X�L�����b�V���i�[�p
	enum WeaponLR
	{
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_MAX
	};
	Weapon*			pWeapon[WeaponLR::TYPE_MAX];

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
	DWORD			m_dwAnim;

	int				m_nCount;			// �ėp�J�E���^�[
	int				m_nCoolDown;
	float			m_fMoveSpeed;
	float			m_fMoveInertia;
	float			m_fMoveAccel;
	float			m_fRiseSpeed;

	// �X�e�[�^�X
	float				m_fHp;



	void	Move(void);
	void	Action(void);
	void	Dash(void);
	void	DashCancel(void);
	//void	Guard(void);
	//void	Action(void);
	void	Jump(void);
	void	MoveFunc(float);
	void	MoveInertia(float fInertia);
	void	RotFunc(D3DXVECTOR3);
	void	SetNum(int nNum) { m_nNum = nNum; }

	// �K�[�h�p
	int		nGuardCount;
	bool	bGuard;


	// �W�����v�p
	float	fVelocity;				// �����x
	float	fGravity;				// �d��
	bool	bJump;					// �W�����v�t���O

	// �_�b�V���p
	D3DXVECTOR3		vDash;			// �ړ��ʏ��
	int				nDashCount;
	bool			bDash;

	void ChangeAnim(DWORD dwAnime, FLOAT fShift);
	void ChangeAnimSpeed(FLOAT _AnimSpeed);
	void SetAnim(void);
	void Player::MoveLimit(void);

public:
	bool SubHp(float fDamage) 
	{
		m_fHp -= fDamage;
		if (m_fHp < 0.0f) return true;
		return false;
	}
	void SetTag(D3DXVECTOR3 vTag) { m_vTag = vTag; }
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }
	D3DXVECTOR3 GetPosWeapon(WeaponLR eLR) { return pWeapon[eLR]->GetPos(); }
	// �ǋL�͋t���i�V�������̂���i�[�����j
	enum PLAYER_ANIME
	{	// �A�j���[�V����
		ATK_LEFT,
		ATK_RIGHT,
		GUARD_CON,
		GUARD,
		RIGHT,	
		LEFT,	
		FRONT,	
		BACK,	
		IDOL,	
		MAX		
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
	static Player		*m_pPlayer[PLAYER_MAX];

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
		SAFE_DELETE(m_pPlayer[player]);
		m_pPlayer[player] = new Type;
		m_pPlayer[player]->m_nNum = int(player);
		m_pPlayer[player]->m_nTagNum = int(PLAYER_2P - player);
		m_pPlayer[player]->m_CSkinMesh = SceneManager::GetCharMgr()->GetCharData(type);
		if (m_pPlayer[player]->m_CSkinMesh)
		{
			m_pPlayer[player]->m_CSkinMesh->ChangeAnim(Player::IDOL, 0.05f);
		}	
	}

	static Player *GetPlayer(PLAYER player) { return m_pPlayer[player]; }
	static D3DXVECTOR3 GetPos(PLAYER player) { return m_pPlayer[player]->GetPos(); }
	static D3DXVECTOR3 GetPosWeapon(PLAYER player, Player::WeaponLR eLR)
	{
		return m_pPlayer[player]->GetPosWeapon(eLR);
	}
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

class Pastry : public Player
{
public:
	Pastry() : Player()
	{
		// �E�F�|�����Z�b�g
		pWeapon[Player::TYPE_LEFT] = WeaponManager::SetWeapon(WeaponManager::BEATER);
		pWeapon[Player::TYPE_RIGHT] = WeaponManager::SetWeapon(WeaponManager::BOWL);
	}
	~Pastry();

};

class Idol : public Player
{
public:
	Idol() : Player()
	{
		// ���f���̏�����
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN, 0.05f);
		//m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN);
	}
	~Idol();

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
