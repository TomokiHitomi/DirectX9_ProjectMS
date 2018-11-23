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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define PLAYER_MODEL				("flower.X")
//#define PLAYER_MODEL				("data/MODEL/Yuko.x")
//#define PLAYER_MODEL_FIREMAN		("data/MODEL/hackadollMMD.x")
//#define PLAYER_MODEL_DOCTOR			("data/MODEL/Yuko.x")

#define PLAYER_POS					(D3DXVECTOR3(0.0f,0.0f,-20.0f))

//#define PLAYER_MODEL_BONE_WING		("No_9_joint_Torso2")
//#define PLAYER_MODEL_BONE_RM		("No_45_joint_RightMiddle2")

// モデルスケール
#define PLAYER_SCL					(0.2f)

#define PLAYER_MOVE_SPEED			(0.5f)

#define PLAYER_ALPHA_TEST			(10)


// テスト用
#define PLAYER_MARGIN_MOVE			(0.03f)
#define PLAYER_MARGIN_GUARD			(0.4f)
#define PLAYER_MARGIN_ATTACK		(1.1f)

#define PLAYER_MOVE_INERTIA			(0.3f)

// アタック
#define PLAYER_ATTACK_CD			(30)		// クールダウン

// ガード
#define PLAYER_GUARD_CD				(30)

// ジャンプ
#define PLAYER_GRAVITY				(0.3f)
#define PLAYER_VELOCITY				(5.0f)

// ダッシュ
#define PLAYER_DASH					(2.0f)

/***** アニメーション *****/

// アニメーションフラグ
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

// アニメーションスピード
#define PLAYER_ANIM_SPEED_DEF	(60.0f / 3000.0f)
#define PLAYER_ANIM_SPEED_DASH	(60.0f / 1000.0f)

#define PLAYER_ANIM_WEIGHT_DEF	(0.1f)


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
	Weapon*			pWeapon[2];

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
	struct 
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

	D3DXMATRIX		m_mtxWorld;			// ワールドマトリクス
	DWORD			m_dwAnim;

	int				m_nCount;			// 汎用カウンター
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

	// ジャンプ用
	float	fVelocity;				// 加速度
	float	fGravity;				// 重力
	bool	bJump;					// ジャンプフラグ

	// ダッシュ用
	D3DXVECTOR3		vDash;			// 移動量情報
	int				nDashCount;
	bool			bDash;

	void ChangeAnim(DWORD dwAnime, FLOAT fShift);
	void ChangeAnimSpeed(FLOAT _AnimSpeed);
	void SetAnim(void);
	void Player::MoveLimit(void);

public:
	void SetTag(D3DXVECTOR3 vTag) { m_vTag = vTag; }
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }

	// 追記は逆順（新しいものから格納される）
	enum PLAYER_ANIME
	{	// アニメーション
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
	Player		*m_pPlayer[PLAYER_MAX];

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
		delete m_pPlayer[player];
		m_pPlayer[player] = new Type;
		m_pPlayer[player]->m_nNum = int(player);
		m_pPlayer[player]->m_nTagNum = int(PLAYER_2P - player);
		m_pPlayer[player]->m_CSkinMesh = SceneManager::GetCharMgr()->GetCharData(type);
		if (m_pPlayer[player]->m_CSkinMesh)
		{
			m_pPlayer[player]->m_CSkinMesh->ChangeAnim(Player::IDOL, 0.05f);
		}	
		// ウェポンをセット
		m_pPlayer[player]->pWeapon[0] = WeaponManager::SetWeapon(m_pPlayer[player]->m_nNum, WeaponManager::LEFT);
		m_pPlayer[player]->pWeapon[1] = WeaponManager::SetWeapon(m_pPlayer[player]->m_nNum, WeaponManager::RIGHT);
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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
