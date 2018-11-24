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

	// ���[���h�s���������
	D3DXMatrixIdentity(&mtxWorld);

	// �����^�C�}�[��������
	nTime = 0;

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
			// ���[���h�ϊ�
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
// �`�揈��
//=============================================================================
void Weapon::Draw(void)
{
	if (bUse)
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

//=============================================================================
// �ݒu����
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
// �ݒu����
//=============================================================================
void Weapon::Remote(float remote)
{
	//D3DXVECTOR3 
	//vMove = D3DXVec3Normalize()
	////vMove 
	////vRemote = remote;
}