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

	Set<Fireman>(PLAYER_1P, CharacterManager::FIREMAN);
	Set<Doctor>(PLAYER_2P, CharacterManager::DOCTOR);
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
		m_nCoolDown--;
		if (m_nCoolDown < 0)
		{
			// 移動処理
			Move();

			//#ifdef _DEBUG
			//		PrintDebugProc("Pos [%f,%f,%f]\n", m_vPos.x, m_vPos.y, m_vPos.z);
			//		PrintDebugProc("Rot [%f,%f,%f]\n", m_vRot.x, m_vRot.y, m_vRot.z);
			//		PrintDebugProc("RotI[%f,%f,%f]\n", m_vRotInertia.x, m_vRotInertia.y, m_vRotInertia.z);
			//		PrintDebugProc("Move[%f,%f,%f]\n", m_vMove.x, m_vMove.y, m_vMove.z);
			//		PrintDebugProc("Spd [%f]\n", m_fMoveSpeed);
			//		PrintDebugProc("mtxX[%f,%f,%f]\n",
			//			m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
			//		PrintDebugProc("mtxY[%f,%f,%f]\n",
			//			m_mtxWorld._21, m_mtxWorld._22, m_mtxWorld._23);
			//		PrintDebugProc("mtxZ[%f,%f,%f]\n",
			//			m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
			//		PrintDebugProc("mtxA[%f,%f,%f]\n",
			//			m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
			//#endif
		}
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

		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ワールド変換
		//WorldConvertAxis(&m_mtxWorld, m_vPos, m_vZ, m_vY, m_vScl);
		WorldConvertXYZ(&m_mtxWorld, m_vPos, m_vRot, m_vScl);

		// ライティングを強めにあてる
		//SetLight(LIGHT_SUB1, TRUE);
		//SetLight(LIGHT_SUB2, TRUE);

		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, PLAYER_ALPHA_TEST);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//// 両面描画する
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//if (m_nNum == 0)
		//{
		if (m_CSkinMesh != NULL)
		{
			// モデルを描画
			m_CSkinMesh->Draw(pDevice, m_mtxWorld);
		}
		//}

		//// 裏面をカリングに戻す
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// αテストを無効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

//#ifdef _DEBUG
		//PrintDebugProc("Bone  [%d]\n", m_CSkinMesh->m_dwBoneCount);
//#endif
		// ライティングを通常に戻す
		//SetLight(LIGHT_SUB1, FALSE);
		//SetLight(LIGHT_SUB2, FALSE);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void Player::Move(void)
{
	// 移動量を初期化
	m_vMove = ZERO_D3DXVECTOR3;

	if (CheckJoyconSize(4) || (CheckJoyconSize(2) && m_nNum == 0))
	{
		D3DXVECTOR3 jcL, jcR;
		jcL = GetJoyconAccel(0 + m_nNum * 2);
		jcR = GetJoyconAccel(1 + m_nNum * 2);

		// アタック処理
		if (jcL.y > PLAYER_MARGIN_ATTACK)
		{
//#ifdef _DEBUG
//			PrintDebugProc("【Attack1】\n");
			if (pWeapon[0])
			{
				D3DXVECTOR3 moveTmp = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
				D3DXVec3Normalize(&moveTmp, &moveTmp);

				if (pWeapon[0]->Set(m_vPos, -moveTmp))
				{
					m_nCoolDown = PLAYER_ATTACK_CD;
				}
			}
//#endif
		}
		if (jcR.y > PLAYER_MARGIN_ATTACK)
		{
//#ifdef _DEBUG
//			PrintDebugProc("【Attack2】\n");
//#endif
			D3DXVECTOR3 moveTmp = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
			D3DXVec3Normalize(&moveTmp, &moveTmp);

			if (pWeapon[1])
			{
				if (pWeapon[1]->Set(m_vPos, -moveTmp))
				{
					m_nCoolDown = PLAYER_ATTACK_CD;
				}
			}
		}

		// ガード処理
		if (jcL.z < -PLAYER_MARGIN_GUARD && jcR.z > PLAYER_MARGIN_GUARD)
		{
//#ifdef _DEBUG
//			PrintDebugProc("【Guard】\n");
//#endif
			m_nCoolDown = PLAYER_GUARD_CD;
		}

		// 移動
		else
		{
			// 前
			if (jcL.y > PLAYER_MARGIN_MOVE && jcR.y > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				MoveFunc(m_vRot.y + D3DX_PI);
			}
			// 後
			else if (jcL.y < -PLAYER_MARGIN_MOVE && jcR.y < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				MoveFunc(m_vRot.y);
			}
			// 左
			if (jcL.z > PLAYER_MARGIN_MOVE && jcR.z > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
			}
			// 右
			else if (jcL.z < -PLAYER_MARGIN_MOVE && jcR.z < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
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
		Dash();
		Jump();
	}
	else if(m_nNum == 0)
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
// ジャンプ処理関数
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
			}
		}
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
// アニメーション設定関数
//=============================================================================
void Player::SetPlayerAnime(DWORD dwAnime, FLOAT fShift)
{
	//dAnime = ANIME_MAX - dAnime - 1;
	//if (dwAnime != m_CSkinMesh->GetAnimTrack())
	//{
		//m_CSkinMesh->ChangeAnim(dwAnime);
		m_CSkinMesh->ChangeAnim(dwAnime, fShift);

	//};
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