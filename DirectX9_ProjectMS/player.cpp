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
extern float		fGyroX;
extern float		fGyroY;
extern float		fGyroZ;

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
		m_pPlayer[i] = NULL;
	}

	Set<Pastry>(PLAYER_1P, CharacterManager::FIREMAN);
	Set<Pastry>(PLAYER_2P, CharacterManager::DOCTOR);
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
	//if (GetKeyboardTrigger(DIK_L))
	//{
	//	m_pPlayer[PLAYER_1P]->m_CSkinMesh = m_CSkinMesh[FIREMAN];
	//	m_pPlayer[PLAYER_1P]->m_CSkinMesh->ChangeAnim(Player::PLAYER_ANIME_RUN, 0.05f);
	//}
	//if (GetKeyboardTrigger(DIK_K))
	//{
	//	m_pPlayer[PLAYER_1P]->m_CSkinMesh = m_CSkinMesh[TEST2];
	//	m_pPlayer[PLAYER_1P]->m_CSkinMesh->ChangeAnim(Player::PLAYER_ANIME_RUN, 0.05f);
	//}
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
// コンストラクタ（初期化処理）
//=============================================================================
Player::Player(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 各プロパティの初期化
	m_vPos = PLAYER_POS;
	m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScl = D3DXVECTOR3(PLAYER_SCL, PLAYER_SCL, PLAYER_SCL);

	m_vMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotInertia = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMoveInertia = 0.3f;

	// クールダウン値
	m_nCoolDown = 0;

	// ガード用
	nGuardCount = 0;
	bGuard = false;

	// ジャンプ用
	fVelocity = PLAYER_VELOCITY;
	fGravity = PLAYER_GRAVITY;
	bJump = false;

	// ダッシュ用
	vDash = ZERO_D3DXVECTOR3;			// 移動量情報
	nDashCount = 0;
	bDash = false;

	m_fMoveSpeed = PLAYER_MOVE_SPEED;
	m_fRiseSpeed = 0.0f;
	m_bUse = true;

	m_CSkinMesh = NULL;

	for (unsigned int i = 0; i < 2; i++)
	{
		pWeapon[i] = NULL;
	}
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
//#ifdef _DEBUG
//	PrintDebugProc("【 PLAYER 】\n");
//#endif

	if (m_bUse)
	{
		// 行動処理
		Action();

		// 移動処理
		Move();

		//#ifdef _DEBUG
		//		PrintDebugProc("Pos [%f,%f,%f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
		//#endif

		// アニメーションを設定
		SetAnim();

		if (m_CSkinMesh != NULL)
		{
			// モデルを更新
			m_CSkinMesh->Update();
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
		// 移動制限処理
		MoveLimit();

		//// 移動量を座標に反映
		//m_vPos += m_vMove;

		//D3DXVECTOR3 vTag = pCube->GetPos();

		RotFunc(m_vTag);

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

		//vTag.y = -10.0f;


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

		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, PLAYER_ALPHA_TEST);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// 両面描画する
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		if (m_CSkinMesh != NULL)
		{
			// モデルを描画
			m_CSkinMesh->Draw(pDevice, m_mtxWorld);
		}

		// 裏面をカリングに戻す
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// αテストを無効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// 行動処理
//=============================================================================
void Player::Action(void)
{
	// クールダウン値を減算
	m_nCoolDown--;
	if (m_nCoolDown < 0)
	{
		// 移動量を初期化
		m_vMove = ZERO_D3DXVECTOR3;

		// アニメーションビットパターンを初期化
		m_dwAnim = 0x00000000l;	// 初期化

		if (CheckJoyconSize(4) || (CheckJoyconSize(2) && m_nNum == 0))
		{
			D3DXVECTOR3 jcL, jcR;
			jcL = GetJoyconAccel(0 + m_nNum * 2);
			jcR = GetJoyconAccel(1 + m_nNum * 2);

			bGuard = false;

			// アタック処理
			if (jcL.y > PLAYER_MARGIN_ATTACK)
			{
				if (pWeapon[TYPE_LEFT])
				{
					D3DXVECTOR3 moveTmp = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
					D3DXVec3Normalize(&moveTmp, &moveTmp);

					if (pWeapon[TYPE_LEFT]->Set(m_vPos, -moveTmp))
					{
						m_dwAnim |= PLAYER_ANIM_ATK_LEFT;
						m_nCoolDown = PLAYER_ATTACK_CD;
						JcRumble(0 + m_nNum * 2, 100, 1);
						return;
					}
				}
			}
			if (jcR.y > PLAYER_MARGIN_ATTACK)
			{
				if (pWeapon[TYPE_RIGHT])
				{
					D3DXVECTOR3 moveTmp = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
					D3DXVec3Normalize(&moveTmp, &moveTmp);

					if (pWeapon[TYPE_RIGHT]->Set(m_vPos, -moveTmp))
					{
						m_dwAnim |= PLAYER_ANIM_ATK_RIGHT;
						m_nCoolDown = PLAYER_ATTACK_CD;
						JcRumble(1 + m_nNum * 2, 100, 1);
						return;
					}
				}
			}

			// ガード処理
			if (jcL.z < -PLAYER_MARGIN_GUARD && jcR.z > PLAYER_MARGIN_GUARD)
			{
				nGuardCount++;
				if (nGuardCount > PLAYER_GUARD_COUNT)
				{
					bGuard = true;
					m_dwAnim |= PLAYER_ANIM_GUARD;
					m_nCoolDown = PLAYER_ATTACK_CD;
					DashCancel();
				}
			}
			else
			{
				nGuardCount = 0;

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

				// ジャンプ
				if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_R))
				{
					bJump = true;
				}

				// ダッシュ
				if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_L))
				{
					bDash = true;
				}
			}

		}
		// Joyconの接続がなかった場合はキーボード操作（移動のみ）
		else if (m_nNum == 0)
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
	Dash();
	Jump();
} 

//=============================================================================
// 移動処理
//=============================================================================
void Player::Move(void)
{
	m_vPos += m_vMove;
}

//=============================================================================
// ジャンプ処理関数
//=============================================================================
void Player::Jump(void)
{
	// ジャンプ中
	if (bJump)
	{
		fVelocity -= fGravity;
		m_vPos.y += fVelocity;
		if (m_vPos.y < 0.0f)
		{
			m_vPos.y = 0.0f;
			fVelocity = PLAYER_VELOCITY;
			fGravity = PLAYER_GRAVITY;
			bJump = false;
		}
	}
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
			m_vMove *= PLAYER_DASH;
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
			if (nDashCount > 20)
			{
				bDash = false;
				nDashCount = 0;
				m_nCoolDown = PLAYER_DASH_CD;
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
// ダッシュキャンセル処理関数
//=============================================================================
void Player::DashCancel(void)
{
	bDash = false;
	nDashCount = 0;
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
	D3DXVECTOR3 vecTemp;
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
	m_vRot.y = atan2(vecTemp.x, vecTemp.z);

	//
	//// 回転先と現在の角度差を計算
	//float fRotDiff;
	//fRotDiff = m_vRotDest.y - m_vRot.y;
	//fRotDiff = PiCalculate180(fRotDiff);

	//// 角度差を適用
	//m_vRot.y += fRotDiff * 0.02f;
	//m_vRot.y = PiCalculate180(m_vRot.y);

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
		m_CSkinMesh->ChangeAnim(dwAnime, fShift);
	}
}

//=============================================================================
// アニメーションスピード設定関数
//=============================================================================
void Player::ChangeAnimSpeed(FLOAT AnimSpeed)
{
	if (m_CSkinMesh != NULL)
	{
		m_CSkinMesh->SetAnimSpeed(AnimSpeed);
	}
}

//=============================================================================
// アニメーション設定関数
//=============================================================================
void Player::SetAnim(void)
{
	// 優先順位ごとに if 分岐
	// 最後までモーションさせたいものにはウェイト値を設定
	if (PLAYER_ANIM_GUARD & m_dwAnim)
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