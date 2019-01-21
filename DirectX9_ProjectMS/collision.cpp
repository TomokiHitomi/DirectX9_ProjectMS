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
#include "plane.h"
#include "calculate.h"
#include "scene.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "joycon.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MoveLimit(D3DXVECTOR3 pos);
bool CheckHitBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1);

//=============================================================================
// �����蔻��֐�
//=============================================================================
void ChackHit(void)
{
	Player* pPlayer;
	Player* pTarget;
	Weapon* pWeapon;

	D3DXVECTOR3 vTarget;
	for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
	{
		// �v���C���[�ƃ^�[�Q�b�g�̃|�C���^���擾
		pPlayer = PlayerManager::GetPlayer((PlayerManager::PLAYER)i);
		pTarget = PlayerManager::GetPlayer((PlayerManager::PLAYER)pPlayer->m_nTagNum);
		for (unsigned int j = 0; j < Player::TYPE_MAX; j++)
		{
			pWeapon = pPlayer->GetWeapon((Player::WeaponLR)j);
			if (pWeapon != NULL)
			{
				if (pWeapon->GetUse())
				{
					vTarget = pTarget->GetPos();
					vTarget.y += PLAYER_HEIGHT_HIT;
					if (CheckHitBC(pWeapon->GetPos(), vTarget,
						PLAYER_SIZE_HIT, pWeapon->GetSize()))
					{
						bool bGuard = true;
						// �K�[�h���Ȃ��
						if (pTarget->m_stAction[Player::AC_GURAD_WU].bUse)
						{
							bGuard = pTarget->SubHpGuard(pWeapon->GetDamage());
							//pTarget->SetPos()
						}
						// �K�[�hHP���Ȃ�������K�[�h�ђ�
						if (bGuard)
						{
							// �^�[�Q�b�g�̃_���[�W�t���O�𗧂Ă�
							pTarget->SetDamage();
							// �q�b�gSE
							SetSe(SE_COLLIDE, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);

							// Joycon�U��
							JcRumble(0 + pTarget->m_nNum * 2, 100, 1);
							JcRumble(1 + pTarget->m_nNum * 2, 100, 1);

							// �^�[�Q�b�g��HP�����Z
							if (pTarget->SubHp(pWeapon->GetDamage()))
							{
								// �����v���C���[��ݒ�
								GameScene::SetRoundWin(pPlayer->m_nNum);
								// �A�j���[�V������ݒ�
								pPlayer->ChangeAnimSpeed(PLAYER_ANIM_SPEED_DEF);
								pPlayer->ChangeAnim(Player::IDOL, PLAYER_ANIM_WEIGHT_DAMAGE);

								//switch (pPlayer->m_nType)
								//{
								//case 0:
								//	pPlayer->ChangeAnim(Player::ATK_SP3, PLAYER_ANIM_WEIGHT_DAMAGE);
								//	break;
								//case 1:
								//case 2:
								//	pPlayer->ChangeAnim(Player::ATK_SP2, PLAYER_ANIM_WEIGHT_DAMAGE);
								//	break;
								//case 3:
								//	pPlayer->ChangeAnim(Player::ATK_SP1, PLAYER_ANIM_WEIGHT_DAMAGE);
								//	break;
								//}

								pTarget->ChangeAnimSpeed(PLAYER_ANIM_SPEED_DEF);
								pTarget->ChangeAnim(Player::DOWN, PLAYER_ANIM_WEIGHT_DAMAGE);
								//if (!BaseScene::bSceneChange) SetFadeScene(SceneManager::RESULT);
								//BaseScene::bSceneChange = true;
							}
						}
						// �v���C���[�̃E�F�|���� false �ɂ���
						pWeapon->SetUse(false);
					}
					// �}�b�v�T�C�Y�ƃE�F�|�����W�̓����蔻��
					bool bHit = CheckHitBoxToPos(ZERO_D3DXVECTOR3,
						pWeapon->GetPos(),
						D3DXVECTOR2(PLANE_SIZE_X * PLANE_X_MAX + CHECK_HIT_MARGIN_BP,
							PLANE_SIZE_Y * PLANE_Y_MAX + CHECK_HIT_MARGIN_BP));
					// �}�b�v�̊O���Ȃ� false
					if (!bHit)pWeapon->SetUse(false);
				}
			}
		}
	}
}

//=============================================================================
// �ړ���������
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
// BB�̔���֐�
//=============================================================================
bool CheckHitBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1)
{
	// �����蔻��̊m�F(BB)
	if (((pos1.x + size1.x) > (pos2.x)) && ((pos2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z)) && ((pos2.z) > (pos1.z - size1.y)))
	{
		// �����蔻��
		return true;
	}
	return false;
}

//=============================================================================
// BB�̔���֐�
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	// �����蔻��̊m�F(BB)
	if (((pos1.x + size1.x) > (pos2.x - size2.x)) && ((pos2.x + size2.x) > (pos1.x - size1.x))
		&& ((pos1.z + size1.y) > (pos2.z - size2.y)) && ((pos2.z + size2.y) > (pos1.z - size1.y)))
	{
		// �����蔻��
		return true;
	}
	return false;
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