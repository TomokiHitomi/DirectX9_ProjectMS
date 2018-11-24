//=============================================================================
//
// ���菈�� [collision.cpp]
// Author : GP12A295 25 �l���F��
//
// �����蔻����s��cpp
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "object.h"
#include "gage3d.h"
#include "gage.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//=============================================================================
// �����蔻��֐�
//=============================================================================
void ChackHit(void)
{
	Player* pPlayer;
	Player* pTarget;

	D3DXVECTOR3 vTarget;
	for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
	{
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
					ObjectManager::GetObjectPointer<Gage3d>(ObjectManager::GAGE3D)->DamegeReduce(PLAYER_DAMAGE_NORMAL, pTarget->m_nNum);
					ObjectManager::GetObjectPointer<Gage>(ObjectManager::GAGE)->DamegeReduce(PLAYER_DAMAGE_NORMAL, pTarget->m_nNum);
					pPlayer->SubHp(PLAYER_DAMAGE_NORMAL);
					pPlayer->pWeapon[(Player::WeaponLR)j]->SetUse(false);
				}
			}
		}
	}
}

//=============================================================================
// BC�̔���֐�
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);

	// �����蔻��̊m�F(BC)
	if (fTempLengthSq <= (size1 + size2)*(size1 + size2))
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// ���C�ƃX�t�B�A�̓����蔻��
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
	{	// ���C�̒�����0
		return false;
	}

	float fS = fB * fB - fA * fC;
	if (fS < 0.0f)
	{	// �Փ˂Ȃ�
		return false;
	}

	fS = sqrtf(fS);
	float fA1 = (fB - fS) / fA;
	float fA2 = (fB + fS) / fA;

	if (fA1 < 0.0f || fA2 < 0.0f)
	{	// ���C�̔��΂ŏՓ�
		return false;
	}

	return true;
}

//=============================================================================
// ���C�ƃ��b�V���̓����蔻��
//=============================================================================
float CheckHitRayToMesh(D3DXVECTOR3 posRay, D3DXVECTOR3 vecRay, LPD3DXBASEMESH lpMesh)
{
	BOOL bHit = false;
	float fDist = 0.0f;

	D3DXIntersect(
		lpMesh,		// �x�[�X���b�V��
		&posRay,	// ���C�̎n�_
		&vecRay,	// ���C�̃x�N�g��
		&bHit,		// �����蔻��[out]
		NULL,		// ���C�ɍł��߂��ʂ̃C���f�b�N�X�l[out]
		NULL,		// �q�b�g���WU[out]
		NULL,		// �q�b�g���WV[out]
		&fDist,		// ���C�̎n�_�����_�܂̂ŋ���[out]
		NULL,		// �q�b�g�������ׂĂ̖ʏ��[out]
		NULL);		// �q�b�g��[out]

	return fDist;
}