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

	// モデルデータを接続
	pXModel = XModel;

	for (UINT i = 0; i < WEAPON_DATA_MAX;i++)
	{
		cWD[i].vPos = ZERO_D3DXVECTOR3;			// 座標情報
		cWD[i].vRot = ZERO_D3DXVECTOR3;			// 回転情報
		cWD[i].vMove = ZERO_D3DXVECTOR3;
		cWD[i].vRemote = ZERO_D3DXVECTOR3;
		cWD[i].nTime = 0;
		cWD[i].bUse = false;		// 使用フラグ
	}

	vScl = WEAPON_SCL_VEC3;				// 拡縮情報
	//vShot = ZERO_D3DXVECTOR3;
	fSize = 0.0f;
	fDamage = 0.0f;
	fRemote = 0.0f;

	// ワールド行列を初期化
	D3DXMatrixIdentity(&mtxWorld);

	//// 生存タイマーを初期化
	//nTime = 0;

	// 回転設定
	bRot = false;
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
	for (UINT i = 0; i < WEAPON_DATA_MAX; i++)
	{
		if (cWD[i].bUse)
		{
			if (cWD[i].nTime < WEAPON_TIME_MAX)
			{
				cWD[i].vPos += cWD[i].vMove * WEAPON_MOVE_SPEED;

				// ワールド変換（回転あり・なし）
				if (bRot)
				{
					// 回転ありの場合は vRot に回転量を加算
					cWD[i].vRot.x -= WEAPON_ROT_SPEED;
					cWD[i].vRot.z -= WEAPON_ROT_SPEED * 0.1f;
					//WorldConvert(&mtxWorld, vPos, vRot, vScl);
				}
				//else WorldConvertAxis(&mtxWorld, vPos, vMove, UP_D3DXVECTOR3, vScl);

				SAFE_UPDATE(pXModel);
				cWD[i].nTime++;
			}
			else
			{
				cWD[i].bUse = false;
			}
		}
#ifdef _DEBUG

		ImGui::Text("Use [%d] Remote[%.2f] Pos [%.2f,%.2f,%.2f] Move[%.2f,%.2f,%.2f]\n",
			cWD[i].bUse, fRemote,
			cWD[i].vPos.x, cWD[i].vPos.y, cWD[i].vPos.z,
			cWD[i].vMove.x, cWD[i].vMove.y, cWD[i].vMove.z);

		//PrintDebugProc("Use [%d] Remote[%f]\n",bUse, fRemote);
		//PrintDebugProc("Pos [%f,%f,%f]\n", vPos.x, vPos.y, vPos.z);
		//PrintDebugProc("Move[%f,%f,%f]\n", vMove.x, vMove.y, vMove.z);
		//PrintDebugProc("\n");
#endif

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Weapon::Draw(void)
{
	if (pXModel != NULL)
	{
		for (UINT i = 0; i < WEAPON_DATA_MAX; i++)
		{
			if (cWD[i].bUse)
			{
				if (cWD[i].nTime > 0)
				{
					// ワールド変換（回転あり・なし）
					if (bRot)
					{
						// 回転ありの場合は vRot に回転量を加算
						WorldConvert(&mtxWorld, cWD[i].vPos, cWD[i].vRot, vScl);
					}
					else WorldConvertAxis(&mtxWorld, cWD[i].vPos, cWD[i].vMove, UP_D3DXVECTOR3, vScl);

					// モデルを描画
					pXModel->Draw(mtxWorld);
				}
			}
		}
	}
}

//=============================================================================
// ステータス設定処理
//=============================================================================
void Weapon::SetStatus(float size, float damage, float scl, bool rot)
{
	fSize = size;
	fDamage = damage;
	bRot = rot;
	vScl = D3DXVECTOR3(scl, scl, scl);
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
	for (UINT i = 0; i < WEAPON_DATA_MAX; i++)
	{
		if (!cWD[i].bUse)
		{
			cWD[i].nTime = 0;
			cWD[i].vPos = pos;
			fRemote = 0.0f;
			//vShot = shot;
			cWD[i].vMove = shot;
			cWD[i].bUse = true;

			D3DXVECTOR3 vUp = UP_D3DXVECTOR3;
			CrossProduct(&cWD[i].vRemote, &shot, &vUp);
			return true;
		}
	}
	return false;
}

//=============================================================================
// 遠隔操作処理
//=============================================================================
void Weapon::Remote(float remote)
{
	for (UINT i = 0; i < WEAPON_DATA_MAX; i++)
	{
		if (cWD[i].bUse)
		{
			// リモート開始時間を上回っていれば
			if (cWD[i].nTime > WEAPON_REMOTE_TIME)
			{
				// リモート値（加速度値）を補正
				remote *= WEAPON_REMOTE_CORRECTION;

				cWD[i].vMove += cWD[i].vRemote * remote;

				// 射出ベクトルと補正したリモートベクトルを足して移動量に代入
				//vMove = vShot + (vRemote * (fRemote));
				// 移動量を正規化
				D3DXVec3Normalize(&cWD[i].vMove, &cWD[i].vMove);
			}
		}
	}
}