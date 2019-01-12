//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

/*******************************************************************************
* インクルード
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
// マクロ定義
//*****************************************************************************

// モデルスケール
#define PLAYER_SCL					(0.25f)

// 初期座標（2Pは対角線に設置）
#define PLAYER_POS					(D3DXVECTOR3(50.0f, 0.0f, 50.0f))

// 移動
#define PLAYER_MOVE_SPEED			(0.4f)
#define PLAYER_MOVE_INERTIA			(0.3f)

// 回転
#define PLAYER_ROT_INERTIA			(0.3f)

// αテスト
#define PLAYER_ALPHA_TEST			(10)

/***** 操作系 *****/

// Joyconのあそび
#define PLAYER_MARGIN_MOVE			(0.05f)
#define PLAYER_MARGIN_GUARD			(0.5f)
#define PLAYER_MARGIN_ATTACK		(1.1f)

// ウェポン
#define PLAYER_WEAPON_SET_XZ		(2.0f)
#define PLAYER_WEAPON_SET_HEIGHT	(7.0f)

// ステータス
#define PLAYER_HP_MAX				(100)
#define PLAYER_SP_MAX				(100)
#define PLAYER_SP_CHARGE_AUTO		(0.05f)
#define PLAYER_SP_CHARGE_ATTACK		(5.0f)

// ダメージ
#define PLAYER_DAMAGE_NORMAL		(6.0f)
#define PLAYER_DAMAGE_SP			(25.0f)
#define PLAYER_DAMAGE_CD			(10)

// アタック
#define PLAYER_ATTACK_CD			(30)		// クールダウン
#define PLAYER_ATTACK_CD_ANIM		(19)		// クールダウン

// ガード
#define PLAYER_GUARD_CD				(5)			// クールダウン
#define PLAYER_GUARD_COUNT			(5)			// ガードスタートカウント
#define PLAYER_GUARD_HP_MAX			(15.0f)		// ガードの耐久値
#define PLAYER_GUARD_HP_RECOVER		(0.2f)		// ガードの耐久回復値

// ジャンプ
#define PLAYER_GRAVITY				(0.2f)
#define PLAYER_VELOCITY				(3.0f)
#define PLAYER_JUMP_CD				(15)			// クールダウン

// ダッシュ
#define PLAYER_DASH_CD				(10)
#define PLAYER_DASH_SPEED			(1.8f)
#define PLAYER_DASH_TIME			(10)

// 当たり判定
#define PLAYER_SIZE_HIT				(5.0f)
#define PLAYER_SIZE_WEAPON			(5.0f)
#define PLAYER_SIZE_WEAPON_SP		(10.0f)
#define PLAYER_HEIGHT_HIT			(7.0f)

/***** アニメーション *****/

// アニメーションフラグ
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

// アニメーションスピード
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
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player
{
public:
	CSkinMesh*		m_CSkinMesh;	// スキンメッシュ格納用
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

	// コンストラクタ（初期化処理）
	Player(void);
	//デストラクタ（終了処理）
	~Player(void);

	// 更新処理
	void	Update(void);
	void	LateUpdate(void);
	// 描画処理
	void	Draw(void);

	int				m_nNum;				// プレイヤーナンバー
	int				m_nTagNum;
	bool			m_bUse;				// 使用フラグ

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
	D3DXVECTOR3		m_vPos;				// 座標情報
	D3DXVECTOR3		m_vRot;				// 回転情報
	D3DXVECTOR3		m_vScl;				// 拡縮情報
	D3DXVECTOR3		m_vMove;			// 移動量情報
	D3DXVECTOR3		m_vRotInertia;		// 回転情報
	D3DXVECTOR3		m_vRotDiff;			// 回転差分
	D3DXVECTOR3		m_vRotDistance;		// 回転距離
	D3DXVECTOR3		m_vRotDest;			// 回転目的地
	D3DXVECTOR3		m_vUp;

	D3DXVECTOR3		m_vTag;				// ターゲット座標
	D3DXVECTOR3		m_vPosGage;			// ゲージ設置座標

	D3DXMATRIX		m_mtxWorld;			// ワールドマトリクス
	DWORD			m_dwAnim;

	int				m_nCount;			// 汎用カウンター
	int				m_nCoolDown;
	float			m_fMoveSpeed;
	float			m_fMoveInertia;
	float			m_fMoveAccel;
	float			m_fRiseSpeed;

	// ステータス
	float				m_fHp;
	float				m_fSp;
	float				m_fGuardHp;
	bool				m_bSpMax;
	bool				m_bSpStandby;

	// ジャンプ
	float	fVelocity;				// 加速度
	float	fGravity;				// 重力
	bool	bJump;					// ジャンプフラグ

	// ダッシュ
	D3DXVECTOR3		vDash;			// 移動量情報
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

	// 追記は逆順（新しいものから格納される）
	enum PLAYER_ANIME
	{	// アニメーション
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
	{	// プレイヤー管理
		PLAYER_1P,
		PLAYER_2P,
		PLAYER_MAX
	};
	static Player		*m_pPlayer[PLAYER_MAX];

public:
	// コンストラクタ（初期化処理）
	PlayerManager(void);
	//デストラクタ（終了処理）
	~PlayerManager(void);

	// 更新処理
	void	Update(void);
	// 描画処理
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
		// スケールをセット
		SetScl(CHARACTER_FIREMAN_SCL);

		// ウェポンをセット
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
		// スケールをセット
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
		// スケールをセット
		SetScl(CHARACTER_PASTRY_SCL);

		// ウェポンをセット
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
		// スケールをセット
		SetScl(CHARACTER_IDOL_SCL);

		// ウェポンをセット
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
// プロトタイプ宣言
//*****************************************************************************

#endif
