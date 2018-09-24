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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define PLAYER_MODEL				("flower.X")
#define PLAYER_MODEL				("hackadollMMD.x")
#define PLAYER_MODEL_WING			("test_wing2.X")
#define PLAYER_MODEL_SWORD			("sword.X")
#define PLAYER_MODEL_SWORD_TEX		("UV_Yat.tga")

#define PLAYER_POS					(D3DXVECTOR3(0.0f,0.0f,-20.0f))

#define PLAYER_WING_SCL				(5.0f)
#define PLAYER_WING_ROT_X			(1.7f)

#define PLAYER_SWORD_MAX			(10)
#define PLAYER_SWORD_SCL			(0.5f)

#define PLAYER_MODEL_BONE_WING		("No_9_joint_Torso2")
#define PLAYER_MODEL_BONE_RM		("No_45_joint_RightMiddle2")

// モデルスケール
#define PLAYER_SCL					(0.1f)

#define PLAYER_MOVE_SPEED			(1.0f)

#define PLAYER_ALPHA_TEST			(10)


// テスト用
#define PLAYER_MARGIN_MOVE			(0.02f)
#define PLAYER_MARGIN_GUARD			(0.3f)
#define PLAYER_MARGIN_ATTACK		(1.1f)

#define PLAYER_MOVE_INERTIA			(0.3f)

// アタック


// ジャンプ
#define PLAYER_GRAVITY				(0.3f)
#define PLAYER_VELOCITY				(5.0f)

// ダッシュ
#define PLAYER_DASH					(5.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player
{
public:
	CSkinMesh		*m_CSkinMesh;	// スキンメッシュ格納用

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

	int				m_nCount;			// 汎用カウンター
	int				m_nCoolDown;
	float			m_fMoveSpeed;
	float			m_fMoveInertia;
	float			m_fMoveAccel;
	float			m_fRiseSpeed;


	void	Move(void);
	void	Dash(void);
	void	Guard(void);
	void	Action(void);
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

public:
	void SetTag(D3DXVECTOR3 vTag) { m_vTag = vTag; }
	D3DXVECTOR3 GetPos(void) { return m_vPos; }
	D3DXVECTOR3 GetTag(void) { return m_vTag; }

	void SetPlayerAnime(DWORD dwAnime, FLOAT fShift);

	enum PLAYER_ANIME
	{
		PLAYER_ANIME_DRUNK,
		PLAYER_ANIME_RUN,
		PLAYER_ANIME_DANCE_SPIN,
		PLAYER_ANIME_DANCE_YMCA,

		PLAYER_ANIME_DEATH,
		PLAYER_ANIME_HEADSHOT,
		PLAYER_ANIME_IDLE_EX,
		PLAYER_ANIME_RECOIL,
		PLAYER_ANIME_OVERDRAW,

		PLAYER_ANIME_JUMP_END,
		PLAYER_ANIME_JUMP_LOOP,
		PLAYER_ANIME_JUMP_START,
		PLAYER_ANIME_AIM_RIGHT,
		PLAYER_ANIME_AIM_LEFT,

		PLAYER_ANIME_AIM_BACK,
		PLAYER_ANIME_AIM_FORWARD,
		PLAYER_ANIME_AIM_IDLE,
		PLAYER_ANIME_RIGHT,
		PLAYER_ANIME_LEFT,

		PLAYER_ANIME_BACK,
		PLAYER_ANIME_FORWARD,
		PLAYER_ANIME_IDLE,
		PLAYER_ANIME_HAND,
		PLAYER_ANIME_MAX
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
	Player *m_pPlayer[PLAYER_MAX];

public:
	// コンストラクタ（初期化処理）
	PlayerManager(void);
	//デストラクタ（終了処理）
	~PlayerManager(void);

	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);

	template <typename Type>
	void Set(PLAYER player)
	{
		if (m_pPlayer[player] != NULL)
		{
			delete m_pPlayer[player];
		}
		m_pPlayer[player] = new Type;
		m_pPlayer[player]->m_nNum = int(player);
		m_pPlayer[player]->m_nTagNum = int(PLAYER_2P - player);
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
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		m_CSkinMesh->Init(pDevice, PLAYER_MODEL);
		m_CSkinMesh->ChangeAnim(PLAYER_ANIME_RUN, 0.05f);
	}
	~Fireman();

};

class Doctor : public Player
{
public:
	Doctor() : Player()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		m_CSkinMesh->Init(pDevice, PLAYER_MODEL);
		m_CSkinMesh->ChangeAnim(PLAYER_ANIME_DANCE_YMCA, 0.05f);
	}
	~Doctor();

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
