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

// ダメージ
#define PLAYER_DAMAGE_NORMAL		(5.0f)
#define PLAYER_DAMAGE_THROW			(10.0f)
#define PLAYER_DAMAGE_SP			(30.0f)
#define PLAYER_DAMAGE_CD			(10)

// アタック
#define PLAYER_ATTACK_CD			(30)		// クールダウン
#define PLAYER_ATTACK_CD_ANIM		(19)		// クールダウン

// ガード
#define PLAYER_GUARD_CD				(30)
#define PLAYER_GUARD_COUNT			(5)		// ガードスタートカウント

// ジャンプ
#define PLAYER_GRAVITY				(0.3f)
#define PLAYER_VELOCITY				(5.0f)

// ダッシュ
#define PLAYER_DASH_CD				(10)
#define PLAYER_DASH_SPEED			(1.5f)
#define PLAYER_DASH_TIME			(10)

// 当たり判定
#define PLAYER_SIZE_HIT				(5.0f)
#define PLAYER_SIZE_WEAPON			(1.0f)
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
#define PLAYER_ANIM_JUMP_END		0x00001000
//#define PLAYER_ANIM_				0x00002000
//#define PLAYER_ANIM_				0x00004000
//#define PLAYER_ANIM_				0x00008000

// アニメーションスピード
#define PLAYER_ANIM_SPEED_DEF		(60.0f / 3000.0f)
#define PLAYER_ANIM_SPEED_DASH		(60.0f / 1000.0f)

#define PLAYER_ANIM_WEIGHT_DEF		(0.1f)
#define PLAYER_ANIM_WEIGHT_ATTACK	(0.3f)
#define PLAYER_ANIM_WEIGHT_GUARD	(0.3f)
#define PLAYER_ANIM_WEIGHT_DAMAGE	(1.0f)

/***** UI *****/
#define PLAYER_GAGE_HEIGHT			(-13.0f)

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
		TYPE_MAX
	};
	Weapon*			pWeapon[WeaponLR::TYPE_MAX];

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
private:
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
		AC_GURAD,
		AC_DAMAGE,
		//AC_DASH,
		//AC_JUMP,
		AC_MAX
	};

	ACTION			m_stAcCD[AC_MAX];

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

	// ジャンプ
	float	fVelocity;				// 加速度
	float	fGravity;				// 重力
	bool	bJump;					// ジャンプフラグ

	// ダッシュ
	D3DXVECTOR3		vDash;			// 移動量情報
	int				nDashCount;
	bool			bDash;

	void	ActionCD(void);
	void	Move(void);
	void	Action(void);
	void	ActionKeyboard(void);

	void	Damage(void);
	void	Dash(void);
	void	DashCancel(void);
	//void	Guard(void);
	void	Attack(WeaponLR eLR);
	void	Jump(void);
	void	MoveFunc(float);
	void	MoveInertia(float fInertia);
	void	RotFunc(D3DXVECTOR3);
	void	SetNum(int nNum) { m_nNum = nNum; }

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
	void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	void SetDamage(void)
	{ 
		m_stAcCD[AC_DAMAGE].bFlag = true;
		m_stAcCD[AC_DAMAGE].nCnt = PLAYER_DAMAGE_CD;
	}
	void InitPos(void);
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetPosGage(void) { return m_vPosGage; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }
	D3DXVECTOR3 GetPosWeapon(WeaponLR eLR) { return pWeapon[eLR]->GetPos(); }
	// 追記は逆順（新しいものから格納される）
	enum PLAYER_ANIME
	{	// アニメーション
		JUMP_END,
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
		// モデルの初期化
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
		// モデルの初期化
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
		// ウェポンをセット
		pWeapon[Player::TYPE_LEFT] =
			WeaponManager::SetWeapon(WeaponManager::CDCASE);
		pWeapon[Player::TYPE_LEFT]->SetRot(true);
		pWeapon[Player::TYPE_LEFT]->SetScl(WEAPON_MODEL_CDCASE_SCL);

		pWeapon[Player::TYPE_RIGHT] =
			WeaponManager::SetWeapon(WeaponManager::MIC);
		pWeapon[Player::TYPE_RIGHT]->SetRot(true);
		pWeapon[Player::TYPE_RIGHT]->SetScl(WEAPON_MODEL_MIC_SCL);
	}
	~Idol();

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
