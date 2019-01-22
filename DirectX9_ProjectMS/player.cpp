//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "calculate.h"
#include "input.h"
#include "camera.h"
#include "cube.h"
#include "sound.h"
#include "joycon.h"
#include "character.h"
#include "weaponMgr.h"
#include "plane.h"
#include "rightleft.h"
#include "game.h"
#include "scene.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player* PlayerManager::m_pPlayer[PlayerManager::PLAYER_MAX];

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
PlayerManager::PlayerManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::PLAYER, Priority::Middle, Priority::Middle);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		// プレイヤーを初期化
		m_pPlayer[i] = NULL;
		// 選択キャラをシーンマネージャーから取得
		int eTemp = SceneManager::GetSelectChar(i);
		// 選択キャラに応じてキャラクターをセット
		switch ((CharacterManager::TYPE)eTemp)
		{
		case CharacterManager::FIREMAN:
			Set<Fireman>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::PASTRY:
			Set<Pastry>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::IDOL:
			Set<Idol>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::DOCTOR:
			Set<Doctor>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		}
	}

	//Set<Idol>(PLAYER_2P, CharacterManager::IDOL);
	//Set<Idol>(PLAYER_1P, CharacterManager::IDOL);
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
PlayerManager::~PlayerManager(void)
{
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		delete m_pPlayer[i];
		m_pPlayer[i] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void PlayerManager::Update(void)
{
#ifdef _DEBUG
	// imguiの更新開始
	ImGui::Begin("Player");
#endif
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->m_bUse)
			{
				m_pPlayer[i]->Update();
			}
		}
	}

	SetTag();

	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->m_bUse)
			{
				m_pPlayer[i]->LateUpdate();
			}
		}
	}
#ifdef _DEBUG
	// imguiの更新終了
	ImGui::End();
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void PlayerManager::Draw(void)
{
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->m_bUse)
			{
				m_pPlayer[i]->Draw();
			}
		}
	}
}

//=============================================================================
// ターゲット座標設定処理
//=============================================================================
void PlayerManager::SetTag(void)
{
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->m_bUse)
			{
				m_pPlayer[i]->SetTag((m_pPlayer[i]->GetPos() + m_pPlayer[m_pPlayer[i]->m_nTagNum]->GetPos()) / 2);
				//m_pPlayer[i]->SetTag(ZERO_D3DXVECTOR3);
			}
		}
	}
}

//=============================================================================
// リセット処理
//=============================================================================
void PlayerManager::Reset(void)
{
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->eLRSp != Player::TYPE_TEMP)
			{
				// ウェポン復元処理
				m_pPlayer[i]->RestoreWeaponSp();
			}
			// ステータスの初期化
			m_pPlayer[i]->InitStatus();
			// 座標の初期化
			m_pPlayer[i]->InitPos();
			// ゲージの初期化
			// 構造上、どちらかのゲージを初期化すれば良いが回しておく
			m_pPlayer[i]->pGage->InitStatus();
			m_pPlayer[i]->pGage3d->InitStatus();
		}
	}
}



//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
Player::Player(void)
{
	// スキンメッシュポインタを NULL に初期化
	m_CSkinMesh = NULL;

	// ステータス初期化
	InitStatus();

	// ウェポンの数だけ NULL に初期化
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		pWeapon[i] = NULL;
	}

	// ゲージのポインタを初期化
	pGage = NULL;
	pGage3d = NULL;
}

//=============================================================================
// ステータス初期化処理
//=============================================================================
void Player::InitStatus(void)
{
	// 各プロパティの初期化
	m_vPos = ZERO_D3DXVECTOR3;
	m_vRot = ZERO_D3DXVECTOR3;
	//m_vScl = D3DXVECTOR3(PLAYER_SCL, PLAYER_SCL, PLAYER_SCL);

	m_vMove = ZERO_D3DXVECTOR3;
	m_vRotInertia = ZERO_D3DXVECTOR3;
	m_vRotDiff = ZERO_D3DXVECTOR3;
	m_vRotDistance = ZERO_D3DXVECTOR3;
	m_vRotDest = ZERO_D3DXVECTOR3;
	m_fMoveInertia = 0.3f;

	// ゲージ設置座標
	m_vPosGage = ZERO_D3DXVECTOR3;

	// ステータス
	m_fHp = PLAYER_HP_MAX;
	m_fSp = 0;
	m_bSpMax = false;
	m_bSpStandby = false;
	m_bSpMode = false;

	// クールダウン値
	m_nCoolDown = 0;

	m_nSpLR = 0;
	m_nSpCount = 0;
	m_nSpFlag = false;

	// 各フラグとウォームアップ・クールダウンの初期化
	for (unsigned int i = 0; i < AC_MAX; i++)
	{
		m_stAction[i].nCnt = 0;
		m_stAction[i].bFlag = false;
		m_stAction[i].bUse = false;
	}

	// ジャンプ
	fVelocity = PLAYER_VELOCITY;
	fGravity = PLAYER_GRAVITY;
	bJump = false;

	// ダッシュ
	vDash = ZERO_D3DXVECTOR3;			// 移動量情報
	nDashCount = 0;
	bDash = false;

	// ガード
	m_fGuardHp = PLAYER_GUARD_HP_MAX;	// 耐久値を設定

	m_fMoveSpeed = PLAYER_MOVE_SPEED;
	m_fRiseSpeed = 0.0f;
	m_bUse = true;

	// SPアタック用 TEMP で初期化
	eLRSp = TYPE_TEMP;

	ChangeAnim(IDOL, PLAYER_ANIM_WEIGHT_MAX);

	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
Player::~Player(void)
{
	if (m_CSkinMesh != NULL)
	{
		//m_CSkinMesh->Release();
		//delete m_CSkinMesh;
		m_CSkinMesh = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Player::Update(void)
{
#ifdef _DEBUG
	//PrintDebugProc("Player[%d]  Hp[%f]  GHp[%f]\n", m_nNum, m_fHp, m_fGuardHp);
	ImGui::Text("Player[%d]  Hp[%f]  GHp[%f]\n", m_nNum, m_fHp, m_fGuardHp);
	//if (ImGui::Button("SpMode = true"))
	//{
	//	m_bSpMode = true;
	//}
#endif

	if (m_bUse)
	{
		// ゲージのポインタが NUUL なら取得
		if (pGage == NULL)
			pGage = ObjectManager::GetObjectPointer<Gage>(ObjectManager::GAGE);
		if (pGage3d == NULL)
			pGage3d = ObjectManager::GetObjectPointer<Gage3d>(ObjectManager::GAGE3D);

		if (GameScene::GetGameFlag())
		{
			// 行動処理
			Action();

			// クールダウン処理
			ActionCD();

			// 移動処理
			Move();

			if (m_fHp <= 0.0f)
				m_dwAnim |= PLAYER_ANIM_DOWN;

			// アニメーションを設定
			SetAnim();

			// SPの自動チャージ
			AddSp(PLAYER_SP_CHARGE_AUTO);
		}

		if (m_CSkinMesh != NULL)
		{
			// モデルを更新
			m_CSkinMesh->Update(m_nNum);
		}
	}

//#ifdef _DEBUG
//	PrintDebugProc("\n");
//#endif
}

//=============================================================================
// 更新処理（Update後に処理される）
//=============================================================================
void Player::LateUpdate(void)
{
	if (m_bUse)
	{
		//// SPの自動チャージ
		//AddSp(PLAYER_SP_CHARGE_AUTO);

		// 移動制限処理
		MoveLimit();

		//// 移動量を座標に反映
		//m_vPos += m_vMove;

		//D3DXVECTOR3 vTag = pCube->GetPos();


		// アタックフラグが立っていなかったら
		if (!m_stAction[AC_ATTACK].bFlag)
		{
			// 回転処理
			RotFunc(m_vTag);
		}

		//// 移動量に慣性を適用
		//MoveInertia(m_fMoveInertia);

		D3DXVECTOR3 vEye, vAt;

		vAt.x = sinf(m_vRot.y) * -200.0f;
		vAt.y = 0.0f;
		vAt.z = cosf(m_vRot.y) * -200.0f;

		vEye.x = sinf(m_vRot.y) * 20.0f;
		vEye.y = 20.0f;
		vEye.z = cosf(m_vRot.y) * 20.0f;

		D3DXVECTOR3 temp = m_vPos - m_vTag;
		temp.y = 0.0f;
		D3DXVec3Normalize(&temp, &temp);
		temp.x *= 20.0f;
		temp.y = 30.0f;
		temp.z *= 20.0f;


		// ゲージ設置座標の算出
		m_vPosGage = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
		D3DXVec3Normalize(&m_vPosGage, &m_vPosGage);

		// ゲージ設置場所を調整してプレイヤーPosにオフセット
		m_vPosGage.x = m_vPos.x + m_vPosGage.x * PLAYER_GAGE_SET_XZ;
		m_vPosGage.z = m_vPos.z + m_vPosGage.z * PLAYER_GAGE_SET_XZ;
		m_vPosGage.y = m_vPos.y + PLAYER_GAGE_HEIGHT;





		// カメラをAtをモデルに設定
		CameraManager::pCamera[m_nNum]->SetAt(m_vTag);
		//Camera::SetAt(m_vTag, m_nNum);

		// カメラEyeをモデル後方にセット
		CameraManager::pCamera[m_nNum]->SetEye(m_vPos + vEye);
		//Camera::SetEye(m_vPos + vEye, m_nNum);

		//// カメラUpをモデル上部に設定
		//Camera::SetUp(m_vY);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Player::Draw(void)
{
	if (m_bUse)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxWing, mtxTemp;		// アニメーション更新処理

		// ワールド変換
		WorldConvertXYZ(&m_mtxWorld, m_vPos, m_vRot, m_vScl);

		if (m_CSkinMesh != NULL)
		{
			if(CameraManager::GetType() == CameraManager::MULTI2) m_CSkinMesh->StopAnim();
			// モデルを描画
			m_CSkinMesh->Draw(pDevice, m_mtxWorld, m_nNum);
			m_CSkinMesh->PlayAnim();
		}
	}
}

//=============================================================================
// 行動処理
//=============================================================================
void Player::Action(void)
{
	// 移動量を初期化
	m_vMove = ZERO_D3DXVECTOR3;

	// アニメーションビットパターンを初期化
	m_dwAnim = 0x00000000l;	// 初期化

	// ダメージ処理
	Damage();

	// Sp減算処理
	SubSp(PLAYER_SP_SUB);

	

	if (CheckJoyconSize(4) || (CheckJoyconSize(2) && m_nNum == 0))
	{
		D3DXVECTOR3 jcL, jcR;
		jcL = GetJoyconAccel(0 + m_nNum * 2);
		jcR = GetJoyconAccel(1 + m_nNum * 2);

		// アタック処理
		if (jcL.y > PLAYER_MARGIN_ATTACK)
		{
			// ウェポンが正常にセットされていたら
			if (pWeapon[TYPE_LEFT])
			{
				// アタックを実行
				Attack(TYPE_LEFT);
			}
		}
		if (jcR.y > PLAYER_MARGIN_ATTACK)
		{
			// ウェポンが正常にセットされていたら
			if (pWeapon[TYPE_RIGHT])
			{
				// アタックを実行
				Attack(TYPE_RIGHT);
			}
		}

		// アタックフラグが立っていればアニメーションビットを立てる
		if (m_stAction[AC_ATTACK_LEFT].bFlag) m_dwAnim |= PLAYER_ANIM_ATK_LEFT;
		else if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_dwAnim |= PLAYER_ANIM_ATK_RIGHT;

		// ガード中でなければ
		if (!m_stAction[AC_GURAD_WU].bFlag)
		{
			// ウェポンを遠隔操作
			pWeapon[TYPE_LEFT]->Remote(jcL.z);
			pWeapon[TYPE_RIGHT]->Remote(jcR.z);
		}

		if (!m_stAction[AC_ATTACK].bFlag)
		{
			// ガード処理
			if (jcL.z < -PLAYER_MARGIN_GUARD && jcR.z > PLAYER_MARGIN_GUARD)
			{
				Guard();
			}
			else
			{
				// ガードフラグを false
				m_stAction[AC_GURAD_WU].bUse = false;
			}
		}

		// アタック・ガード中でなければ
		if(!m_stAction[AC_GURAD_WU].bUse && !m_stAction[AC_GURAD_CD].bFlag && !m_stAction[AC_ATTACK].bFlag)
		{
			// ガードの耐久値回復
			m_fGuardHp += PLAYER_GUARD_HP_RECOVER;
			if (m_fGuardHp > PLAYER_GUARD_HP_MAX) m_fGuardHp = PLAYER_GUARD_HP_MAX;

			// 移動
			bool bMove = false;
			float fMoveAccel = 0.0f;
			// 前
			if (jcL.y > PLAYER_MARGIN_MOVE && jcR.y > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				fMoveAccel = m_fMoveAccel;
				MoveFunc(m_vRot.y + D3DX_PI);
				m_dwAnim |= PLAYER_ANIM_FRONT;
			}
			// 後
			else if (jcL.y < -PLAYER_MARGIN_MOVE && jcR.y < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				fMoveAccel = m_fMoveAccel;
				MoveFunc(m_vRot.y);
				m_dwAnim |= PLAYER_ANIM_BACK;
			}
			// 左
			if (jcL.z > PLAYER_MARGIN_MOVE && jcR.z > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
				if (fMoveAccel < m_fMoveAccel)
				{
					m_dwAnim |= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim ^= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim |= PLAYER_ANIM_LEFT;
				}
			}
			// 右
			else if (jcL.z < -PLAYER_MARGIN_MOVE && jcR.z < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
				if (fMoveAccel < m_fMoveAccel)
				{
					m_dwAnim |= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim ^= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim |= PLAYER_ANIM_RIGHT;
				}
			}

			if (!bJump)
			{
				// ジャンプ
				if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_R))
				{
				// カウント開始
				m_stAction[AC_JUMP_CD].bFlag = true;
				// カウント値を設定
				m_stAction[AC_JUMP_CD].nCnt = PLAYER_JUMP_CD;
				bJump = true;

				}
			}

			if (!bDash)
			{
				// ダッシュ
				if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_L))
				{
					bDash = true;
					SetSe(SE_DASH, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
				}
			}
		}
		// SPアタック処理
		ChangeWeaponSp();
	}
	// Joyconの接続がなかった場合はキーボード操作（移動のみ）
	else
	{
		ActionKeyboard();
	}
	AttackUpdate();
	Dash();
	Jump();
} 

//=============================================================================
// 行動処理（キーボード）
//=============================================================================
void Player::ActionKeyboard(void)
{
	if (m_nNum == 0)
	{
		m_fMoveAccel = 1.0f;
		if (GetKeyboardPress(DIK_W))
		{
			MoveFunc(m_vRot.y + D3DX_PI);
		}
		else if (GetKeyboardPress(DIK_S))
		{
			MoveFunc(m_vRot.y);
		}

		if (GetKeyboardPress(DIK_A))
		{
			MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
		}
		else if (GetKeyboardPress(DIK_D))
		{
			MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
		}
	}

	else if (m_nNum == 1)
	{
		m_fMoveAccel = 1.0f;
		if (GetKeyboardPress(DIK_UP))
		{
			MoveFunc(m_vRot.y + D3DX_PI);
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			MoveFunc(m_vRot.y);
		}

		if (GetKeyboardPress(DIK_LEFT))
		{
			MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{
			MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
		}
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void Player::Move(void)
{
	m_vPos += m_vMove;
}

//=============================================================================
// クールダウン処理
//=============================================================================
void Player::ActionCD(void)
{
	for (unsigned int i = 0; i < AC_MAX; i++)
	{
		// フラグが true ならば
		if (m_stAction[i].bFlag)
		{
			// クールダウンを減算
			m_stAction[i].nCnt--;
			// 0を下回ったら
			if(m_stAction[i].nCnt < 0)
			{
				// フラグを false
				m_stAction[i].bFlag = false;
				// 使用フラグを true
				m_stAction[i].bUse = true;
			}
		}
	}
}

//=============================================================================
// ダメージ処理
//=============================================================================
void Player::Damage(void)
{
	// ダメージフラグが true ならば
	if (m_stAction[AC_DAMAGE].bFlag)
	{
		// ダメージ１のアニメーションフラグを立てる
		m_dwAnim |= PLAYER_ANIM_DAMAGE_1;
	}
}

//=============================================================================
// アタック処理関数
//=============================================================================
void Player::Attack(WeaponLR eLR)
{
	// 設置可能状態であれば
	if (SetRightLeft((int)eLR + m_nNum * 2))
	{
		if (m_bSpMode)
		{
			SetSe(SE_DOCTOR_THROW, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);


			if (eLR == TYPE_LEFT)
			{
				// RIGHT のフラグが立っていたら false にする
				if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_stAction[AC_ATTACK_RIGHT].bFlag = false;
				// フラグを立てる
				m_stAction[AC_ATTACK_LEFT].bFlag = true;
				// クールダウン値を代入
				m_stAction[AC_ATTACK_LEFT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}
			else if (eLR == TYPE_RIGHT)
			{
				// LEFT のフラグが立っていたら false にする
				if (m_stAction[AC_ATTACK_LEFT].bFlag)m_stAction[AC_ATTACK_LEFT].bFlag = false;
				// フラグを立てる
				m_stAction[AC_ATTACK_RIGHT].bFlag = true;
				// クールダウン値を代入
				m_stAction[AC_ATTACK_RIGHT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}

			// フラグを立てる
			m_stAction[AC_ATTACK].bFlag = true;
			// クールダウン値を代入
			m_stAction[AC_ATTACK].nCnt = PLAYER_ATTACK_CD;

			// 設置座標の算出
			D3DXVECTOR3 posTmp = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
			D3DXVec3Normalize(&posTmp, &posTmp);

			// RIGHT の場合は設置posが反対側
			if (eLR == TYPE_RIGHT)posTmp *= -1.0f;

			// 設置場所を調整してプレイヤーPosにオフセット
			posTmp.x = m_vPos.x + posTmp.x * PLAYER_WEAPON_SET_XZ;
			posTmp.z = m_vPos.z + posTmp.z * PLAYER_WEAPON_SET_XZ;
			posTmp.y = m_vPos.y + PLAYER_WEAPON_SET_HEIGHT;

			// 移動ベクトルの算出
			D3DXVECTOR3 moveTmp = m_vTag;
			moveTmp.y += PLAYER_HEIGHT_HIT;
			moveTmp = moveTmp - posTmp;
			D3DXVec3Normalize(&moveTmp, &moveTmp);

			// ウェポンをセット
			pWeapon[eLR]->Set(posTmp, moveTmp);

			// Joycon振動
			JcRumble((int)eLR + m_nNum * 2, 99, 1);

		}
		else
		{
			if (m_nSpCount <= PLAYER_ATTACK_START && m_nSpFlag)
			{
				m_nSpLR = (int)TYPE_SP;
			}
			else
			{
				m_nSpLR = (int)eLR;
			}
			m_nSpFlag = true;
		}
	}


}

//=============================================================================
// アタック処理関数
//=============================================================================
void Player::AttackUpdate(void)
{
	if (!m_bSpMode)
	{
		if (m_nSpFlag)
		{
			m_nSpCount++;
		}

		if (m_nSpCount > PLAYER_ATTACK_START)
		{
			m_nSpCount = 0;
			m_nSpFlag = false;

			// SPチャージ
			AddSp(PLAYER_SP_CHARGE_ATTACK);

			//// SPアタックが準備済み
			//if (m_bSpStandby)
			//{
			//	// Spを初期化
			//	ResetSp();
			//	// スタンバイフラグを false
			//	m_bSpStandby = false;
			//}
			//else if (eLRSp != TYPE_TEMP)
			//{
			//	// ウェポン復元処理
			//	RestoreWeaponSp();
			//}
			//else
			SetSe(SE_DOCTOR_THROW, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);


			if (m_nSpLR == TYPE_LEFT || m_nSpLR == TYPE_SP)
			{
				// RIGHT のフラグが立っていたら false にする
				if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_stAction[AC_ATTACK_RIGHT].bFlag = false;
				// フラグを立てる
				m_stAction[AC_ATTACK_LEFT].bFlag = true;
				// クールダウン値を代入
				m_stAction[AC_ATTACK_LEFT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}
			else if (m_nSpLR == TYPE_RIGHT)
			{
				// LEFT のフラグが立っていたら false にする
				if (m_stAction[AC_ATTACK_LEFT].bFlag)m_stAction[AC_ATTACK_LEFT].bFlag = false;
				// フラグを立てる
				m_stAction[AC_ATTACK_RIGHT].bFlag = true;
				// クールダウン値を代入
				m_stAction[AC_ATTACK_RIGHT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}

			// フラグを立てる
			m_stAction[AC_ATTACK].bFlag = true;
			// クールダウン値を代入
			m_stAction[AC_ATTACK].nCnt = PLAYER_ATTACK_CD;

			// 設置座標の算出
			D3DXVECTOR3 posTmp = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
			D3DXVec3Normalize(&posTmp, &posTmp);

			// RIGHT の場合は設置posが反対側
			if (m_nSpLR == TYPE_RIGHT)posTmp *= -1.0f;

			// 設置場所を調整してプレイヤーPosにオフセット
			posTmp.x = m_vPos.x + posTmp.x * PLAYER_WEAPON_SET_XZ;
			posTmp.z = m_vPos.z + posTmp.z * PLAYER_WEAPON_SET_XZ;
			posTmp.y = m_vPos.y + PLAYER_WEAPON_SET_HEIGHT;

			// 移動ベクトルの算出
			D3DXVECTOR3 moveTmp = m_vTag;
			moveTmp.y += PLAYER_HEIGHT_HIT;
			moveTmp = moveTmp - posTmp;
			D3DXVec3Normalize(&moveTmp, &moveTmp);

			// ウェポンをセット
			pWeapon[m_nSpLR]->Set(posTmp, moveTmp);

			// Joycon振動
			if (m_nSpLR == TYPE_SP)
			{
				JcRumble((int)0 + m_nNum * 2, 99, 1);
				JcRumble((int)1 + m_nNum * 2, 99, 1);
			}
			else
			{				
				JcRumble((int)m_nSpLR + m_nNum * 2, 99, 1);
			}
		}
	}
}


//=============================================================================
// SPウェポン変更処理
//=============================================================================
void Player::ChangeWeaponSp(void)
{
	// Spが最大値の場合
	if (m_bSpMax)
	{
		// Joyconで
		if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_ZL)
			|| JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_ZR))
		{
			m_bSpMax = false;
			m_bSpMode = true;
			SetSe(SE_ATKSP, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
		}
	}

	//if (m_bSpMax && !m_bSpStandby)
	//{
	//	// Joyconで
	//	if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_ZL))
	//	{
	//		// LEFTのポインタをテンポラリに保管
	//		pWeapon[Player::TYPE_TEMP] = pWeapon[Player::TYPE_LEFT];
	//		// LEFTにSPを接続
	//		pWeapon[Player::TYPE_LEFT] = pWeapon[Player::TYPE_SP];
	//		// 接続先を格納
	//		eLRSp = TYPE_LEFT;
	//		// スタンバイフラグを true
	//		m_bSpStandby = true;
	//	}
	//	else if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_ZR))
	//	{
	//		// RIGHTのポインタをテンポラリに保管
	//		pWeapon[Player::TYPE_TEMP] = pWeapon[Player::TYPE_RIGHT];
	//		// RIGHTにSPを接続
	//		pWeapon[Player::TYPE_RIGHT] = pWeapon[Player::TYPE_SP];
	//		// 接続先を格納
	//		eLRSp = TYPE_RIGHT;
	//		// スタンバイフラグを true
	//		m_bSpStandby = true;
	//	}
	//}
	
}

//=============================================================================
// ウェポン復元処理
//=============================================================================
void Player::RestoreWeaponSp(void)
{
	// ウェポンのポインタを復元する
	pWeapon[eLRSp] = pWeapon[Player::TYPE_TEMP];
	// フラグを TEMP に戻す
	eLRSp = TYPE_TEMP;
}

//=============================================================================
// SP加算処理
//=============================================================================
void Player::AddSp(float fSp)
{
	if (!m_bSpMode)
	{
		m_fSp += fSp;
		pGage->SkillAdd(fSp, m_nNum);
		pGage3d->SkillAdd(fSp, m_nNum);
		if (m_fSp >= PLAYER_SP_MAX)
		{
			m_fSp = PLAYER_SP_MAX;
			if (!m_bSpMax)
				SetSe(SE_SP_MAX, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
			m_bSpMax = true;
			return;
		}
		m_bSpMax = false;
	}
}

//=============================================================================
// SP減算処理
//=============================================================================
void Player::SubSp(float fSp)
{
	if (m_bSpMode)
	{
		SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
		SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);

		m_fSp -= fSp;
		pGage->SkillReduce(fSp, m_nNum);
		pGage3d->SkillReduce(fSp, m_nNum);
		if (m_fSp < 0)
		{
			m_fSp = 0;
			if (m_bSpMode)
				SetSe(SE_SP_MAX, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
			m_bSpMode = false;
			SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
			SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);

			return;
		}
	}

	//if (GetKeyboardTrigger(DIK_Z))
	//{
	//	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	//	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	//}
	//else if (GetKeyboardTrigger(DIK_X))
	//{
	//	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
	//	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
	//}
	//m_bSpMax = false;
}

//=============================================================================
// SPリセット
//=============================================================================
void Player::ResetSp(void)
{
	m_fSp = 0.0f;
	pGage->SkillReduce(PLAYER_SP_MAX, m_nNum);
	pGage3d->SkillReduce(PLAYER_SP_MAX, m_nNum);
}

//=============================================================================
// HP減算処理
//=============================================================================
bool Player::SubHp(float fDamage)
{
	m_fHp -= fDamage;
	// ターゲットのゲージHPを減算
	pGage->DamegeReduce(fDamage, m_nNum);
	pGage3d->DamegeReduce(fDamage, m_nNum);
	if (m_fHp <= 0.0f) return true;
	return false;
}

//=============================================================================
// ガードHP減算処理
//=============================================================================
bool Player::SubHpGuard(float fDamage)
{
	m_fGuardHp -= fDamage;
	if (m_fGuardHp < 0.0f)
	{
		m_fGuardHp = 0.0f;
		return true;
	}
	return false;
}

//=============================================================================
// ダメージクールダウン設定処理
//=============================================================================
void Player::SetDamage(void)
{
	m_stAction[AC_DAMAGE].bFlag = true;
	m_stAction[AC_DAMAGE].nCnt = PLAYER_DAMAGE_CD;
}


//=============================================================================
// ガード処理関数
//=============================================================================
void Player::Guard(void)
{
	// ガードフラグとカウントフラグが false ならば
	if (!m_stAction[AC_GURAD_WU].bUse && !m_stAction[AC_GURAD_WU].bFlag)
	{
		// カウント開始
		m_stAction[AC_GURAD_WU].bFlag = true;
		// カウント値を設定
		m_stAction[AC_GURAD_WU].nCnt = PLAYER_GUARD_COUNT;
	}

	// 使用フラグが true ならば
	if (m_stAction[AC_GURAD_WU].bUse)
	{
		// ガードアニメーションをセット
		m_dwAnim |= PLAYER_ANIM_GUARD;
		// ダッシュをキャンセル
		DashCancel();

		// フラグを立てる
		m_stAction[AC_GURAD_CD].bFlag = true;
		// クールダウン値を代入
		m_stAction[AC_GURAD_CD].nCnt = PLAYER_GUARD_CD;
	}
}


//=============================================================================
// ジャンプ処理関数
//=============================================================================
void Player::Jump(void)
{
	// ジャンプ中
	if (bJump)
	{
		//// ジャンプクールダウンフラグが true
		//if (m_stAction[AC_JUMP_CD].bFlag)
		//{
			// ジャンプスタートアニメーションをセット
			m_dwAnim |= PLAYER_ANIM_JUMP_START;
		//}
		//else
		//{
		//	// ジャンプスタートアニメーションをセット
		//	m_dwAnim |= PLAYER_ANIM_JUMP;
		//}

		fVelocity -= fGravity;
		m_vPos.y += fVelocity;
		if (m_vPos.y <= 0.0f)
		{
			//// カウント開始
			//m_stAction[AC_JUMP_END_CD].bFlag = true;
			//// カウント値を設定
			//m_stAction[AC_JUMP_END_CD].nCnt = PLAYER_JUMP_CD;

			m_vPos.y = 0.0f;
			fVelocity = PLAYER_VELOCITY;
			fGravity = PLAYER_GRAVITY;
			bJump = false;
			//m_dwAnim |= PLAYER_ANIM_JUMP_END;
		}
	}
//	if(m_stAction[AC_JUMP_END_CD].bFlag)
//		m_dwAnim |= PLAYER_ANIM_JUMP_END;
}

//=============================================================================
// ダッシュキャンセル処理関数
//=============================================================================
void Player::DashCancel(void)
{
	bDash = false;
	nDashCount = 0;
}

//=============================================================================
// ダッシュ処理関数
//=============================================================================
void Player::Dash(void)
{
	// ダッシュ中
	if (bDash)
	{
		if (nDashCount == 0)
		{
			// ジャンプ中であれば
			if (bJump)
			{
				// ジャンプ加速度をリセット
				fVelocity = 0.0f;
			}
			// 直前の移動ベクトルを正規化
			D3DXVec3Normalize(&m_vMove, &m_vMove);
			// 正規化した移動ベクトルにダッシュ速度を乗算
			m_vMove *= PLAYER_DASH_SPEED;
			// 移動ベクトルを保管
			vDash = m_vMove;
			// ダッシュカウントをインクリメント
			nDashCount++;
		}
		else
		{
			// 保管していた移動ベクトルを渡す
			m_vMove = vDash;
			// ダッシュカウントをインクリメント
			nDashCount++;
			// ダッシュカウントが指定値以上の場合はダッシュ終了
			if (nDashCount > PLAYER_DASH_TIME)
			{
				bDash = false;
				nDashCount = 0;
			}
		}
		ChangeAnimSpeed(PLAYER_ANIM_SPEED_DASH);
	}
	else
	{
		ChangeAnimSpeed(PLAYER_ANIM_SPEED_DEF);
	}
}


//=============================================================================
// 移動処理関数
//=============================================================================
void Player::MoveFunc(float fAngle)
{
	m_vMove.x += sinf(fAngle) * m_fMoveSpeed * m_fMoveAccel;
	m_vMove.z += cosf(fAngle) * m_fMoveSpeed * m_fMoveAccel;
}

//=============================================================================
// 回転処理関数
//=============================================================================
void Player::RotFunc(D3DXVECTOR3 vTag)
{
	D3DXVECTOR3		vecTemp;
	float			fRotTemp;
	//vecTemp.x = vTag.x - m_vPos.x;
	//vecTemp.z = vTag.z - m_vPos.z;

	vecTemp.x = m_vPos.x - vTag.x;
	vecTemp.z = m_vPos.z - vTag.z;


	// atan2のエラー防止
	if (vecTemp.x == 0 && vecTemp.z == 0)
	{
		vecTemp.x += 0.00001;
	}

	// 角度計算
	//m_vRotDest.y = atan2(vecTemp.x, vecTemp.z);
	fRotTemp = atan2(vecTemp.x, vecTemp.z);

	//
	//// 回転先と現在の角度差を計算
	//float fRotDiff;
	//fRotDiff = m_vRotDest.y - m_vRot.y;

	fRotTemp -= m_vRot.y;
	fRotTemp = PiCalculate180(fRotTemp);


	m_vRot.y += fRotTemp * PLAYER_ROT_INERTIA;

	//// 角度差を適用
	//m_vRot.y += fRotDiff * 0.02f;
	m_vRot.y = PiCalculate180(m_vRot.y);

}


//=============================================================================
// 慣性処理関数
//=============================================================================
void Player::MoveInertia(float fInertia)
{
	m_vMove.x += (0.0f - m_vMove.x) * fInertia;
	m_vMove.y += (0.0f - m_vMove.y) * fInertia;
	m_vMove.z += (0.0f - m_vMove.z) * fInertia;
}

//=============================================================================
// アニメーション変更関数
//=============================================================================
void Player::ChangeAnim(DWORD dwAnime, FLOAT fShift)
{
	if (m_CSkinMesh != NULL)
	{
		m_CSkinMesh->ChangeAnim(dwAnime, fShift, m_nNum);
	}
}

//=============================================================================
// アニメーションスピード設定関数
//=============================================================================
void Player::ChangeAnimSpeed(FLOAT AnimSpeed)
{
	if (m_CSkinMesh != NULL)
	{
		m_CSkinMesh->SetAnimSpeed(AnimSpeed, m_nNum);
	}
}

//=============================================================================
// アニメーション設定関数
//=============================================================================
void Player::SetAnim(void)
{
	// 優先順位ごとに if 分岐
	if (PLAYER_ANIM_DUMMY & m_dwAnim);
	else if (PLAYER_ANIM_DOWN & m_dwAnim)
		ChangeAnim(DOWN, PLAYER_ANIM_WEIGHT_DAMAGE);
	else if (PLAYER_ANIM_DAMAGE_1 & m_dwAnim)
	{
		ChangeAnim(DAMAGE_1, PLAYER_ANIM_WEIGHT_DAMAGE);
	}
	else if (PLAYER_ANIM_GUARD & m_dwAnim)
	{
		ChangeAnim(GUARD_CON, PLAYER_ANIM_WEIGHT_GUARD);
	}
	else if (PLAYER_ANIM_ATK_RIGHT & m_dwAnim)
	{
		ChangeAnim(ATK_RIGHT, PLAYER_ANIM_WEIGHT_ATTACK);
	}
	else if (PLAYER_ANIM_ATK_LEFT & m_dwAnim)
	{
		ChangeAnim(ATK_LEFT, PLAYER_ANIM_WEIGHT_ATTACK);
	}
	else if (PLAYER_ANIM_JUMP_END & m_dwAnim)
	{
		ChangeAnim(JUMP_END, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_JUMP & m_dwAnim)
	{
		ChangeAnim(JUMP, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_JUMP_START & m_dwAnim)
	{
		ChangeAnim(JUMP_START, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_FRONT & m_dwAnim)
	{
		ChangeAnim(FRONT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_BACK & m_dwAnim)
	{
		ChangeAnim(BACK, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_LEFT & m_dwAnim)
	{
		ChangeAnim(LEFT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_RIGHT & m_dwAnim)
	{
		ChangeAnim(RIGHT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else
	{
		ChangeAnim(IDOL, PLAYER_ANIM_WEIGHT_DEF);
	}
}

//=============================================================================
// 移動制限処理
//=============================================================================
void Player::MoveLimit(void)
{
	float fLimit;
	fLimit = PLANE_SIZE_X * PLANE_X_MAX;
	if (m_vPos.x > fLimit) m_vPos.x = fLimit;
	if (m_vPos.x < -fLimit)m_vPos.x = -fLimit;

	fLimit = PLANE_SIZE_Y * PLANE_Y_MAX;
	if (m_vPos.z > fLimit) m_vPos.z = fLimit;
	if (m_vPos.z < -fLimit)m_vPos.z = -fLimit;
}

//=============================================================================
// 座標初期化処理
//=============================================================================
void Player::InitPos(void)
{
	if (m_nNum == 0)m_vPos = PLAYER_POS;
	else m_vPos = PLAYER_POS * -1.0f;
}




//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
//Fireman::Fireman(void)
//{
//
//}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
Fireman::~Fireman(void)
{
}