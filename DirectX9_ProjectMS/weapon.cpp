//=============================================================================
//
// �E�F�|������ [weapon.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "weapon.h"
#include "calculate.h"
#include "player.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
Weapon::Weapon(CXModel* XModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���f���f�[�^�|�C���^��NULL�ŏ�����
	pXModel = NULL;

	// ���f���f�[�^��ڑ�
	pXModel = XModel;

	for (UINT i = 0; i < WEAPON_DATA_MAX;i++)
	{
		cWD[i].vPos = ZERO_D3DXVECTOR3;			// ���W���
		cWD[i].vRot = ZERO_D3DXVECTOR3;			// ��]���
		cWD[i].vMove = ZERO_D3DXVECTOR3;
		cWD[i].vRemote = ZERO_D3DXVECTOR3;
		cWD[i].nTime = 0;
		cWD[i].bUse = false;		// �g�p�t���O
	}

	vScl = WEAPON_SCL_VEC3;				// �g�k���
	//vShot = ZERO_D3DXVECTOR3;
	fSize = 0.0f;
	fDamage = 0.0f;
	fRemote = 0.0f;

	// ���[���h�s���������
	D3DXMatrixIdentity(&mtxWorld);

	//// �����^�C�}�[��������
	//nTime = 0;

	// ��]�ݒ�
	bRot = false;
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
Weapon::~Weapon(void)
{
	//SAFE_RELEASE(pXModel);
}

//=============================================================================
// �X�V����
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

				// ���[���h�ϊ��i��]����E�Ȃ��j
				if (bRot)
				{
					// ��]����̏ꍇ�� vRot �ɉ�]�ʂ����Z
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
// �`�揈��
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
					// ���[���h�ϊ��i��]����E�Ȃ��j
					if (bRot)
					{
						// ��]����̏ꍇ�� vRot �ɉ�]�ʂ����Z
						WorldConvert(&mtxWorld, cWD[i].vPos, cWD[i].vRot, vScl);
					}
					else WorldConvertAxis(&mtxWorld, cWD[i].vPos, cWD[i].vMove, UP_D3DXVECTOR3, vScl);

					// ���f����`��
					pXModel->Draw(mtxWorld);
				}
			}
		}
	}
}

//=============================================================================
// �X�e�[�^�X�ݒ菈��
//=============================================================================
void Weapon::SetStatus(float size, float damage, float scl, bool rot)
{
	fSize = size;
	fDamage = damage;
	bRot = rot;
	vScl = D3DXVECTOR3(scl, scl, scl);
}


//=============================================================================
// �X�P�[���ݒ菈��
//=============================================================================
void Weapon::SetScl(float fScl)
{
	vScl = D3DXVECTOR3(fScl, fScl, fScl);
}

//=============================================================================
// ��]�ݒ菈��
//=============================================================================
void Weapon::SetRot(bool bUse)
{
	bRot = bUse;
}

//=============================================================================
// �ݒu����
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
// ���u���쏈��
//=============================================================================
void Weapon::Remote(float remote)
{
	for (UINT i = 0; i < WEAPON_DATA_MAX; i++)
	{
		if (cWD[i].bUse)
		{
			// �����[�g�J�n���Ԃ������Ă����
			if (cWD[i].nTime > WEAPON_REMOTE_TIME)
			{
				// �����[�g�l�i�����x�l�j��␳
				remote *= WEAPON_REMOTE_CORRECTION;

				cWD[i].vMove += cWD[i].vRemote * remote;

				// �ˏo�x�N�g���ƕ␳���������[�g�x�N�g���𑫂��Ĉړ��ʂɑ��
				//vMove = vShot + (vRemote * (fRemote));
				// �ړ��ʂ𐳋K��
				D3DXVec3Normalize(&cWD[i].vMove, &cWD[i].vMove);
			}
		}
	}
}