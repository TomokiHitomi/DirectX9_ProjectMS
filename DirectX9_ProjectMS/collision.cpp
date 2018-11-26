//=============================================================================
//
// 判定処理 [collision.cpp]
// Author : GP12A295 25 人見友基
//
// 当たり判定を行うcpp
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "object.h"
#include "gage3d.h"
#include "gage.h"
#include "plane.h"
#include "calculate.h"
#include "scene.h"
#include "fade.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MoveLimit(D3DXVECTOR3 pos);
bool CheckHitBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1);

//=============================================================================
// 当たり判定関数
//=============================================================================
void ChackHit(void)
{
	Player* pPlayer;
	Player* pTarget;

	D3DXVECTOR3 vTarget;
	for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
	{
		// プレイヤーとターゲットのポインタを取得
		pPlayer = PlayerManager::GetPlayer((PlayerManager::PLAYER)i);
		pTarget = PlayerManager::GetPlayer((PlayerManager::PLAYER)pPlayer->m_nTagNum);
		for (unsigned int j = 0; j < Player::TYPE_MAX; j++)
		{
			if (pPlayer->pWeapon[(Player::WeaponLR)j]->GetUse())
			{
				vTarget = pTarget->GetPos();
				vTarget.y += PLAYER_HEIGHT_HIT;
				if (CheckHitBC(pPlayer->GetPosWeapon((Player::WeaponLR)j), vTarget,
					PLAYER_SIZE_HIT, PLAYER_SIZE_WEAPON))
				{
					bool bGuard = true;
					// ガード中ならば
					if (pTarget->m_stAction[Player::AC_GURAD_WU].bUse)
					{
						bGuard = pTarget->SubHpGuard(PLAYER_DAMAGE_NORMAL);
					}
					// ガードHPがなかったらガード貫通
					if(bGuard)
					{
						// ターゲットのゲージHPを減算
						pTarget->pGage->DamegeReduce(PLAYER_DAMAGE_NORMAL, pTarget->m_nNum);
						pTarget->pGage3d->DamegeReduce(PLAYER_DAMAGE_NORMAL, pTarget->m_nNum);
						// ターゲットのダメージフラグを立てる
						pTarget->SetDamage();
						// ターゲットのHPを減算
						if (pTarget->SubHp(PLAYER_DAMAGE_NORMAL))
						{
							if (!BaseScene::bSceneChange) SetFadeScene(SceneManager::RESULT);
							BaseScene::bSceneChange = true;
						}
					}
					// プレイヤーのウェポンを false にする
					pPlayer->pWeapon[(Player::WeaponLR)j]->SetUse(false);
				}
				// マップサイズとウェポン座標の当たり判定
				bool bHit = CheckHitBoxToPos(ZERO_D3DXVECTOR3,
					pPlayer->pWeapon[(Player::WeaponLR)j]->GetPos(),
					D3DXVECTOR2(PLANE_SIZE_X * PLANE_X_MAX + CHECK_HIT_MARGIN_BP,
						PLANE_SIZE_Y * PLANE_Y_MAX + CHECK_HIT_MARGIN_BP));
				// マップの外側なら false
				if (!bHit)pPlayer->pWeapon[(Player::WeaponLR)j]->SetUse(false);
			}
		}
	}
}

//=============================================================================
// 移動制限処理
//=============================================================================
void MoveLimit(D3DXVECTOR3 pos)
{
	float fLimit;
	fLimit = PLANE_SIZE_X * PLANE_X_MAX;
	if (pos.x > fLimit) pos.x = fLimit;
	if (pos.x < -fLimit)pos.x = -fLimit;

	fLimit = PLANE_SIZE_Y * PLANE_Y_MAX;
	if (pos.z > fLimit) pos.z = fLimit;
	if (pos.z < -fLimit)pos.z = -fLimit;
}

//=============================================================================
// BBの判定関数
//=============================================================================
bool CheckHitBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1)
{
	// 当たり判定の確認(BB)
	if (((pos1.x + size1.x) > (pos2.x)) && ((pos2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z)) && ((pos2.z) > (pos1.z - size1.y)))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// BBの判定関数
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// 当たり判定の確認(BB)
	if (((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z - size2.y)) && ((pos2.z + size2.y) > (pos1.z - size1.y)))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// BCの判定関数
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// 当たり判定の確認(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2))
	{
		// 当たり判定
		return true;
	}
	return false;
}

//=============================================================================
// レイとスフィアの当たり判定
//=============================================================================
bool CheckHitRayToSphere(D3DXVECTOR3 posRay, D3DXVECTOR3 vecRay, D3DXVECTOR3 posTag, float nLength)
{
	posTag.x -= posRay.x;
	posTag.y -= posRay.y;
	posTag.z -= posRay.z;

	float fA = vecRay.x * vecRay.x + vecRay.y * vecRay.y + vecRay.z * vecRay.z;
	float fB = vecRay.x * posTag.x + vecRay.y * posTag.y + vecRay.z * posTag.z;
	float fC = posTag.x * posTag.x + posTag.y * posTag.y + posTag.z * posTag.z - nLength * nLength;

	if (fA == 0.0f)
	{	// レイの長さが0
		return false;
	}

	float fS = fB * fB - fA * fC;
	if (fS < 0.0f)
	{	// 衝突なし
		return false;
	}

	fS = sqrtf(fS);
	float fA1 = (fB - fS) / fA;
	float fA2 = (fB + fS) / fA;

	if (fA1 < 0.0f || fA2 < 0.0f)
	{	// レイの反対で衝突
		return false;
	}

	return true;
}

//=============================================================================
// レイとメッシュの当たり判定
//=============================================================================
float CheckHitRayToMesh(D3DXVECTOR3 posRay, D3DXVECTOR3 vecRay, LPD3DXBASEMESH lpMesh)
{
	BOOL bHit = false;
	float fDist = 0.0f;

	D3DXIntersect(
		lpMesh,		// ベースメッシュ
		&posRay,	// レイの始点
		&vecRay,	// レイのベクトル
		&bHit,		// 当たり判定[out]
		NULL,		// レイに最も近い面のインデックス値[out]
		NULL,		// ヒット座標U[out]
		NULL,		// ヒット座標V[out]
		&fDist,		// レイの始点から交点まので距離[out]
		NULL,		// ヒットしたすべての面情報[out]
		NULL);		// ヒット回数[out]

	return fDist;
}