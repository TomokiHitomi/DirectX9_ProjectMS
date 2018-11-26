//=============================================================================
//
// ウェポン処理 [weapon.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "weapon.h"
#include "calculate.h"
#include "player.h"

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


//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
Weapon::Weapon(CXModel* XModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// モデルデータポインタをNULLで初期化
	pXModel = NULL;

	// モデルデータをインスタンス化
	pXModel = XModel;

	vPos = ZERO_D3DXVECTOR3;			// 座標情報
	vRot = ZERO_D3DXVECTOR3;			// 回転情報
	vScl = WEAPON_SCL_VEC3;				// 拡縮情報
	vMove = ZERO_D3DXVECTOR3;
	vShot = ZERO_D3DXVECTOR3;
	vRemote = ZERO_D3DXVECTOR3;

	fRemote = 0.0f;

	// ワールド行列を初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 生存タイマーを初期化
	nTime = 0;

	// 回転設定
	bRot = false;

	// 使用フラグ
	bUse = false;
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
Weapon::~Weapon(void)
{
	//SAFE_RELEASE(pXModel);
}

//=============================================================================
// 更新処理
//=============================================================================
void Weapon::Update(void)
{
	if (bUse)
	{
		if (nTime < WEAPON_TIME_MAX)
		{
			vPos += vMove * WEAPON_MOVE_SPEED;

			// ワールド変換（回転あり・なし）
			if (bRot)
			{
				// 回転ありの場合は vRot に回転量を加算
				vRot.x -= WEAPON_ROT_SPEED;
				vRot.z -= WEAPON_ROT_SPEED * 0.1f;
				WorldConvert(&mtxWorld, vPos, vRot, vScl);
			}
			else WorldConvertAxis(&mtxWorld, vPos, vMove, UP_D3DXVECTOR3, vScl);

			SAFE_UPDATE(pXModel);
			nTime++;
		}
		else
		{
			bUse = false;
		}
	}

#ifdef _DEBUG
		PrintDebugProc("Use [%d] Remote[%f]\n",bUse, fRemote);
		PrintDebugProc("Pos [%f,%f,%f]\n", vPos.x, vPos.y, vPos.z);
		PrintDebugProc("Move[%f,%f,%f]\n", vMove.x, vMove.y, vMove.z);
		PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void Weapon::Draw(void)
{
	if (bUse)
	{
		if (nTime > 0)
		{
			if (pXModel != NULL)
			{
				LPDIRECT3DDEVICE9 pDevice = GetDevice();
				//// 両面描画する
				//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				// モデルを描画
				pXModel->Draw(mtxWorld);
				//// 裏面をカリングに戻す
				//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}
		}
	}
}

//=============================================================================
// スケール設定処理
//=============================================================================
void Weapon::SetScl(float fScl)
{
	vScl = D3DXVECTOR3(fScl, fScl, fScl);
}

//=============================================================================
// 回転設定処理
//=============================================================================
void Weapon::SetRot(bool bUse)
{
	bRot = bUse;
}

//=============================================================================
// 設置処理
//=============================================================================
bool Weapon::Set(D3DXVECTOR3 pos, D3DXVECTOR3 shot)
{
	nTime = 0;
	vPos = pos;
	fRemote = 0.0f;
	vShot = shot;
	vMove = vShot;
	bUse = true;

	D3DXVECTOR3 vUp = UP_D3DXVECTOR3;
	CrossProduct(&vRemote, &vShot, &vUp);
	return true;
}

//=============================================================================
// 遠隔操作処理
//=============================================================================
void Weapon::Remote(float remote)
{
	if (bUse)
	{
		// リモート開始時間を上回っていれば
		if (nTime > WEAPON_REMOTE_TIME)
		{
			// リモート値（加速度値）を補正
			remote *= WEAPON_REMOTE_CORRECTION;

			//// １フレームあたりに代入できる時間に補正
			//if (remote > WEAPON_REMOTE_ADD_MAX) remote = WEAPON_REMOTE_ADD_MAX;
			//else if (remote < -WEAPON_REMOTE_ADD_MAX) remote = -WEAPON_REMOTE_ADD_MAX;

			//// リモート値を加算
			//fRemote += remote;

			//// 最大値以内に補正
			//if (fRemote > WEAPON_REMOTE_MAX) fRemote = WEAPON_REMOTE_MAX;
			//else if (fRemote < -WEAPON_REMOTE_MAX) fRemote = -WEAPON_REMOTE_MAX;

			vMove += vRemote * remote;


			// 射出ベクトルと補正したリモートベクトルを足して移動量に代入
			//vMove = vShot + (vRemote * (fRemote));
			// 移動量を正規化
			D3DXVec3Normalize(&vMove, &vMove);
		}
	}
}