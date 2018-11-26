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

	// ���f���f�[�^���C���X�^���X��
	pXModel = XModel;

	vPos = ZERO_D3DXVECTOR3;			// ���W���
	vRot = ZERO_D3DXVECTOR3;			// ��]���
	vScl = WEAPON_SCL_VEC3;				// �g�k���
	vMove = ZERO_D3DXVECTOR3;
	vShot = ZERO_D3DXVECTOR3;
	vRemote = ZERO_D3DXVECTOR3;

	fRemote = 0.0f;

	// ���[���h�s���������
	D3DXMatrixIdentity(&mtxWorld);

	// �����^�C�}�[��������
	nTime = 0;

	// ��]�ݒ�
	bRot = false;

	// �g�p�t���O
	bUse = false;
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
	if (bUse)
	{
		if (nTime < WEAPON_TIME_MAX)
		{
			vPos += vMove * WEAPON_MOVE_SPEED;

			// ���[���h�ϊ��i��]����E�Ȃ��j
			if (bRot)
			{
				// ��]����̏ꍇ�� vRot �ɉ�]�ʂ����Z
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
// �`�揈��
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
				//// ���ʕ`�悷��
				//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				// ���f����`��
				pXModel->Draw(mtxWorld);
				//// ���ʂ��J�����O�ɖ߂�
				//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}
		}
	}
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
// ���u���쏈��
//=============================================================================
void Weapon::Remote(float remote)
{
	if (bUse)
	{
		// �����[�g�J�n���Ԃ������Ă����
		if (nTime > WEAPON_REMOTE_TIME)
		{
			// �����[�g�l�i�����x�l�j��␳
			remote *= WEAPON_REMOTE_CORRECTION;

			//// �P�t���[��������ɑ���ł��鎞�Ԃɕ␳
			//if (remote > WEAPON_REMOTE_ADD_MAX) remote = WEAPON_REMOTE_ADD_MAX;
			//else if (remote < -WEAPON_REMOTE_ADD_MAX) remote = -WEAPON_REMOTE_ADD_MAX;

			//// �����[�g�l�����Z
			//fRemote += remote;

			//// �ő�l�ȓ��ɕ␳
			//if (fRemote > WEAPON_REMOTE_MAX) fRemote = WEAPON_REMOTE_MAX;
			//else if (fRemote < -WEAPON_REMOTE_MAX) fRemote = -WEAPON_REMOTE_MAX;

			vMove += vRemote * remote;


			// �ˏo�x�N�g���ƕ␳���������[�g�x�N�g���𑫂��Ĉړ��ʂɑ��
			//vMove = vShot + (vRemote * (fRemote));
			// �ړ��ʂ𐳋K��
			D3DXVec3Normalize(&vMove, &vMove);
		}
	}
}