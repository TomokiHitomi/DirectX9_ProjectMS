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

	// ワールド行列を初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 生存タイマーを初期化
	nTime = 0;

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
			// ワールド変換
			WorldConvertAxis(&mtxWorld, vPos, vMove, UP_D3DXVECTOR3, vScl);
			SAFE_UPDATE(pXModel);
			nTime++;
		}
		else
		{
			bUse = false;
		}
	}

#ifdef _DEBUG
		PrintDebugProc("Use [%d]\n",bUse);
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

//=============================================================================
// 設置処理
//=============================================================================
bool Weapon::Set(D3DXVECTOR3 pos, D3DXVECTOR3 shot)
{
	if (!bUse)
	{
		nTime = 0;
		vPos = pos;
		vPos.y += WEAPON_HEIGHT;

		vShot = shot;
		vMove = vShot;
		bUse = true;

		D3DXVECTOR3 vUp = UP_D3DXVECTOR3;
		CrossProduct(&vRemote, &vUp, &vShot);

		return true;
	}
	return false;
}

//=============================================================================
// 設置処理
//=============================================================================
void Weapon::Remote(float remote)
{
	//D3DXVECTOR3 
	//vMove = D3DXVec3Normalize()
	////vMove 
	////vRemote = remote;
}