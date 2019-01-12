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
#include "gage.h"
#include "gage3d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// ���f���X�P�[��
#define PLAYER_SCL					(0.25f)

// �������W�i2P�͑Ίp���ɐݒu�j
#define PLAYER_POS					(D3DXVECTOR3(50.0f, 0.0f, 50.0f))

// �ړ�
#define PLAYER_MOVE_SPEED			(0.4f)
#define PLAYER_MOVE_INERTIA			(0.3f)

// ��]
#define PLAYER_ROT_INERTIA			(0.3f)

// ���e�X�g
#define PLAYER_ALPHA_TEST			(10)

/***** ����n *****/

// Joycon�̂�����
#define PLAYER_MARGIN_MOVE			(0.05f)
#define PLAYER_MARGIN_GUARD			(0.5f)
#define PLAYER_MARGIN_ATTACK		(1.1f)

// �E�F�|��
#define PLAYER_WEAPON_SET_XZ		(2.0f)
#define PLAYER_WEAPON_SET_HEIGHT	(7.0f)

// �X�e�[�^�X
#define PLAYER_HP_MAX				(100)
#define PLAYER_SP_MAX				(100)
#define PLAYER_SP_CHARGE_AUTO		(0.05f)
#define PLAYER_SP_CHARGE_ATTACK		(5.0f)

// �_���[�W
#define PLAYER_DAMAGE_NORMAL		(6.0f)
#define PLAYER_DAMAGE_SP			(25.0f)
#define PLAYER_DAMAGE_CD			(10)

// �A�^�b�N
#define PLAYER_ATTACK_CD			(30)		// �N�[���_�E��
#define PLAYER_ATTACK_CD_ANIM		(19)		// �N�[���_�E��

// �K�[�h
#define PLAYER_GUARD_CD				(5)			// �N�[���_�E��
#define PLAYER_GUARD_COUNT			(5)			// �K�[�h�X�^�[�g�J�E���g
#define PLAYER_GUARD_HP_MAX			(15.0f)		// �K�[�h�̑ϋv�l
#define PLAYER_GUARD_HP_RECOVER		(0.2f)		// �K�[�h�̑ϋv�񕜒l

// �W�����v
#define PLAYER_GRAVITY				(0.2f)
#define PLAYER_VELOCITY				(3.0f)
#define PLAYER_JUMP_CD				(15)			// �N�[���_�E��

// �_�b�V��
#define PLAYER_DASH_CD				(10)
#define PLAYER_DASH_SPEED			(1.8f)
#define PLAYER_DASH_TIME			(10)

// �����蔻��
#define PLAYER_SIZE_HIT				(5.0f)
#define PLAYER_SIZE_WEAPON			(5.0f)
#define PLAYER_SIZE_WEAPON_SP		(10.0f)
#define PLAYER_HEIGHT_HIT			(7.0f)

/***** �A�j���[�V���� *****/

// �A�j���[�V�����t���O
#define PLAYER_ANIM_FRONT			0x00000001
#define PLAYER_ANIM_BACK			0x00000002
#define PLAYER_ANIM_LEFT			0x00000004
#define PLAYER_ANIM_RIGHT			0x00000008
#define PLAYER_ANIM_GUARD			0x00000010
#define PLAYER_ANIM_ATK_RIGHT		0x00000020
#define PLAYER_ANIM_ATK_LEFT		0x00000040
#define PLAYER_ANIM_DAMAGE_1		0x00000080
#define PLAYER_ANIM_DAMAGE_2		0x00000100
#define PLAYER_ANIM_JUMP_START		0x00000200
#define PLAYER_ANIM_JUMP			0x00001000
#define PLAYER_ANIM_JUMP_END		0x00002000
//#define PLAYER_ANIM_				0x00004000
//#define PLAYER_ANIM_				0x00008000

// �A�j���[�V�����X�s�[�h
#define PLAYER_ANIM_SPEED_DEF		(60.0f / 3500.0f)
#define PLAYER_ANIM_SPEED_DASH		(60.0f / 1500.0f)

#define PLAYER_ANIM_WEIGHT_DEF		(0.1f)
#define PLAYER_ANIM_WEIGHT_ATTACK	(0.3f)
#define PLAYER_ANIM_WEIGHT_GUARD	(0.3f)
#define PLAYER_ANIM_WEIGHT_DAMAGE	(1.0f)
#define PLAYER_ANIM_WEIGHT_JUMP		(0.5f)

/***** UI *****/
#define PLAYER_GAGE_SET_XZ			(3.0f)
#define PLAYER_GAGE_HEIGHT			(-11.0f)

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
		TYPE_SP,
		TYPE_TEMP,
		TYPE_MAX
	};
	Weapon*		pWeapon[WeaponLR::TYPE_MAX];
	WeaponLR	eLRSp;

	Gage*		pGage;
	Gage3d*		pGage3d;

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

	typedef struct
	{
		int		nCnt;
		bool	bFlag;
		bool	bUse;
	}ACTION;

	enum ACTION_LIST
	{
		AC_ATTACK_LEFT,
		AC_ATTACK_RIGHT,
		AC_ATTACK,
		AC_GURAD_WU,
		AC_GURAD_CD,
		AC_DAMAGE,
		//AC_DASH,
		AC_JUMP_CD,
		AC_JUMP_END_CD,
		AC_MAX
	};

	ACTION			m_stAction[AC_MAX];

private:
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
	D3DXVECTOR3		m_vPosGage;			// �Q�[�W�ݒu���W

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
	float				m_fSp;
	float				m_fGuardHp;
	bool				m_bSpMax;
	bool				m_bSpStandby;

	// �W�����v
	float	fVelocity;				// �����x
	float	fGravity;				// �d��
	bool	bJump;					// �W�����v�t���O

	// �_�b�V��
	D3DXVECTOR3		vDash;			// �ړ��ʏ��
	int				nDashCount;
	bool			bDash;

	void ActionCD(void);
	void ChangeWeaponSp(void);

	void Move(void);
	void Action(void);
	void ActionKeyboard(void);
	void Damage(void);
	void Dash(void);
	void DashCancel(void);
	void Guard(void);
	void Attack(WeaponLR eLR);
	void Jump(void);
	void MoveFunc(float);
	void MoveInertia(float fInertia);
	void RotFunc(D3DXVECTOR3);
	void SetNum(int nNum) { m_nNum = nNum; }
	void SetAnim(void);
	void Player::MoveLimit(void);

public:
	void ChangeAnim(DWORD dwAnime, FLOAT fShift);
	void ChangeAnimSpeed(FLOAT _AnimSpeed);
	void InitStatus(void);
	void RestoreWeaponSp(void);
	void AddSp(float fSp);
	void ResetSp(void);
	bool SubHp(float fDamage);
	bool SubHpGuard(float fDamage);
	void SetTag(D3DXVECTOR3 vTag) { m_vTag = vTag; }
	void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	void SetScl(float scl) { m_vScl = D3DXVECTOR3(scl, scl, scl); }
	void SetDamage(void);
	void InitPos(void);
	float GetHp(void) { return m_fHp; }
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetPosGage(void) { return m_vPosGage; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }
	D3DXVECTOR3 GetPosWeapon(WeaponLR eLR) { return pWeapon[eLR]->GetPos(); }
	Weapon* GetWeapon(WeaponLR eLR) { return pWeapon[eLR]; }

	// �ǋL�͋t���i�V�������̂���i�[�����j
	enum PLAYER_ANIME
	{	// �A�j���[�V����
		JUMP_END,
		JUMP,
		JUMP_START,
		DAMAGE_2,
		DAMAGE_1,
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
		m_pPlayer[player]->InitPos();
		m_pPlayer[player]->m_CSkinMesh = SceneManager::GetCharMgr()->GetCharData(type);
		if (m_pPlayer[player]->m_CSkinMesh)
		{
			m_pPlayer[player]->m_CSkinMesh->ChangeAnim(Player::IDOL, 0.05f, m_pPlayer[player]->m_nNum);
		}	
	}

	static void Reset(void);
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
		// �X�P�[�����Z�b�g
		SetScl(CHARACTER_FIREMAN_SCL);

		// �E�F�|�����Z�b�g
		pWeapon[Player::TYPE_LEFT] =
			WeaponManager::SetWeapon(WeaponManager::EXTINGUISHER);
		pWeapon[Player::TYPE_LEFT]->SetStatus(
			PLAYER_SIZE_WEAPON, PLAYER_DAMAGE_NORMAL,
			WEAPON_MODEL_EXTINGUISHER_SCL, true);

		pWeapon[Player::TYPE_RIGHT] =
			WeaponManager::SetWeapon(WeaponManager::HELMET);
		pWeapon[Player::TYPE_RIGHT]->SetStatus(
			PLAYER_SIZE_WEAPON, PLAYER_DAMAGE_NORMAL,
			WEAPON_MODEL_HELMET_SCL, true);

		pWeapon[Player::TYPE_SP] =
			WeaponManager::SetWeapon(WeaponManager::FIREENGIN);
		pWeapon[Player::TYPE_SP]->SetStatus(
			PLAYER_SIZE_WEAPON_SP, PLAYER_DAMAGE_SP,
			WEAPON_MODEL_FIREENGIN_SCL, false);
	}
	~Fireman();

};

class Doctor : public Player
{
public:
	Doctor() : Player()
	{
		// �X�P�[�����Z�b�g
		SetScl(CHARACTER_DOCTOR_SCL);
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
		// �X�P�[�����Z�b�g
		SetScl(CHARACTER_PASTRY_SCL);

		// �E�F�|�����Z�b�g
		pWeapon[Player::TYPE_LEFT] =
			WeaponManager::SetWeapon(WeaponManager::BEATER);
		pWeapon[Player::TYPE_LEFT]->SetRot(true);
		pWeapon[Player::TYPE_LEFT]->SetScl(WEAPON_MODEL_BEATER_SCL);

		pWeapon[Player::TYPE_RIGHT] =
			WeaponManager::SetWeapon(WeaponManager::BOWL);
		pWeapon[Player::TYPE_RIGHT]->SetRot(true);
		pWeapon[Player::TYPE_RIGHT]->SetScl(WEAPON_MODEL_BOWL_SCL);
	}
	~Pastry();

};

class Idol : public Player
{
public:
	Idol() : Player()
	{
		// �X�P�[�����Z�b�g
		SetScl(CHARACTER_IDOL_SCL);

		// �E�F�|�����Z�b�g
		pWeapon[Player::TYPE_LEFT] =
			WeaponManager::SetWeapon(WeaponManager::CDCASE);
		pWeapon[Player::TYPE_LEFT]->SetStatus(
			PLAYER_SIZE_WEAPON, PLAYER_DAMAGE_NORMAL,
			WEAPON_MODEL_CDCASE_SCL, true);

		pWeapon[Player::TYPE_RIGHT] =
			WeaponManager::SetWeapon(WeaponManager::MIC);
		pWeapon[Player::TYPE_RIGHT]->SetStatus(
			PLAYER_SIZE_WEAPON, PLAYER_DAMAGE_NORMAL,
			WEAPON_MODEL_MIC_SCL, true);

		pWeapon[Player::TYPE_SP] =
			WeaponManager::SetWeapon(WeaponManager::KARAAGE);
		pWeapon[Player::TYPE_SP]->SetStatus(
			PLAYER_SIZE_WEAPON_SP, PLAYER_DAMAGE_SP,
			WEAPON_MODEL_KARAAGE_SCL, false);
	}
	~Idol();

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
