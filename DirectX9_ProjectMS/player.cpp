//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP12A295 25 �l���F��
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
extern float		fGyroX;
extern float		fGyroY;
extern float		fGyroZ;

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
PlayerManager::PlayerManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::PLAYER, Priority::Middle, Priority::Middle);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		m_pPlayer[i] = NULL;
	}

	Set<Fireman>(PLAYER_1P, CharacterManager::FIREMAN);
	Set<Doctor>(PLAYER_2P, CharacterManager::DOCTOR);
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
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
// �X�V����
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
// �`�揈��
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
// �^�[�Q�b�g���W�ݒ菈��
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
// �R���X�g���N�^�i�����������j
//=============================================================================
Player::Player(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�v���p�e�B�̏�����
	m_vPos = PLAYER_POS;
	m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScl = D3DXVECTOR3(PLAYER_SCL, PLAYER_SCL, PLAYER_SCL);

	m_vMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotInertia = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMoveInertia = 0.3f;

	// �N�[���_�E���l
	m_nCoolDown = 0;

	// �W�����v�p
	fVelocity = PLAYER_VELOCITY;
	fGravity = PLAYER_GRAVITY;
	bJump = false;


	// �_�b�V���p
	vDash = ZERO_D3DXVECTOR3;			// �ړ��ʏ��
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
// �f�X�g���N�^�i�I�������j
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
// �X�V����
//=============================================================================
void Player::Update(void)
{
//#ifdef _DEBUG
//	PrintDebugProc("�y PLAYER �z\n");
//#endif

	if (m_bUse)
	{
		m_nCoolDown--;
		if (m_nCoolDown < 0)
		{
			// �ړ�����
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
			// ���f�����X�V
			m_CSkinMesh->Update();
		}
	}

//#ifdef _DEBUG
//	PrintDebugProc("\n");
//#endif
}

//=============================================================================
// �X�V�����iUpdate��ɏ��������j
//=============================================================================
void Player::LateUpdate(void)
{
	if (m_bUse)
	{
		//// �ړ��ʂ����W�ɔ��f
		//m_vPos += m_vMove;

		//D3DXVECTOR3 vTag = pCube->GetPos();

		RotFunc(m_vTag);

		//// �ړ��ʂɊ�����K�p
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


			// �J������At�����f���ɐݒ�
			CameraManager::pCamera[m_nNum]->SetAt(m_vTag);
			//Camera::SetAt(m_vTag, m_nNum);

			// �J����Eye�����f������ɃZ�b�g
			CameraManager::pCamera[m_nNum]->SetEye(m_vPos + vEye);
			//Camera::SetEye(m_vPos + vEye, m_nNum);

			//// �J����Up�����f���㕔�ɐݒ�
			//Camera::SetUp(m_vY);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Player::Draw(void)
{
	if (m_bUse)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxWing, mtxTemp;		// �A�j���[�V�����X�V����

		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ���[���h�ϊ�
		//WorldConvertAxis(&m_mtxWorld, m_vPos, m_vZ, m_vY, m_vScl);
		WorldConvertXYZ(&m_mtxWorld, m_vPos, m_vRot, m_vScl);

		// ���C�e�B���O�����߂ɂ��Ă�
		//SetLight(LIGHT_SUB1, TRUE);
		//SetLight(LIGHT_SUB2, TRUE);

		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, PLAYER_ALPHA_TEST);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//// ���ʕ`�悷��
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//if (m_nNum == 0)
		//{
		if (m_CSkinMesh != NULL)
		{
			// ���f����`��
			m_CSkinMesh->Draw(pDevice, m_mtxWorld);
		}
		//}

		//// ���ʂ��J�����O�ɖ߂�
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// ���e�X�g�𖳌���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

//#ifdef _DEBUG
		//PrintDebugProc("Bone  [%d]\n", m_CSkinMesh->m_dwBoneCount);
//#endif
		// ���C�e�B���O��ʏ�ɖ߂�
		//SetLight(LIGHT_SUB1, FALSE);
		//SetLight(LIGHT_SUB2, FALSE);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void Player::Move(void)
{
	// �ړ��ʂ�������
	m_vMove = ZERO_D3DXVECTOR3;

	if (CheckJoyconSize(4) || (CheckJoyconSize(2) && m_nNum == 0))
	{
		D3DXVECTOR3 jcL, jcR;
		jcL = GetJoyconAccel(0 + m_nNum * 2);
		jcR = GetJoyconAccel(1 + m_nNum * 2);

		// �A�^�b�N����
		if (jcL.y > PLAYER_MARGIN_ATTACK)
		{
//#ifdef _DEBUG
//			PrintDebugProc("�yAttack1�z\n");
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
//			PrintDebugProc("�yAttack2�z\n");
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

		// �K�[�h����
		if (jcL.z < -PLAYER_MARGIN_GUARD && jcR.z > PLAYER_MARGIN_GUARD)
		{
//#ifdef _DEBUG
//			PrintDebugProc("�yGuard�z\n");
//#endif
			m_nCoolDown = PLAYER_GUARD_CD;
		}

		// �ړ�
		else
		{
			// �O
			if (jcL.y > PLAYER_MARGIN_MOVE && jcR.y > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				MoveFunc(m_vRot.y + D3DX_PI);
			}
			// ��
			else if (jcL.y < -PLAYER_MARGIN_MOVE && jcR.y < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				MoveFunc(m_vRot.y);
			}
			// ��
			if (jcL.z > PLAYER_MARGIN_MOVE && jcR.z > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
			}
			// �E
			else if (jcL.z < -PLAYER_MARGIN_MOVE && jcR.z < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
			}

			// �W�����v
			if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_R))
			{
				bJump = true;
			}

			// �_�b�V��
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
// �W�����v�����֐�
//=============================================================================
void Player::Jump(void)
{
	// �W�����v��
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
// �W�����v�����֐�
//=============================================================================
void Player::Dash(void)
{
	// �_�b�V����
	if (bDash)
	{
		if (nDashCount == 0)
		{
			// �W�����v���ł����
			if (bJump)
			{
				// �W�����v�����x�����Z�b�g
				fVelocity = 0.0f;
			}
			// ���O�̈ړ��x�N�g���𐳋K��
			D3DXVec3Normalize(&m_vMove, &m_vMove);
			// ���K�������ړ��x�N�g���Ƀ_�b�V�����x����Z
			m_vMove *= PLAYER_DASH;
			// �ړ��x�N�g����ۊ�
			vDash = m_vMove;
			// �_�b�V���J�E���g���C���N�������g
			nDashCount++;
		}
		else
		{
			// �ۊǂ��Ă����ړ��x�N�g����n��
			m_vMove = vDash;
			// �_�b�V���J�E���g���C���N�������g
			nDashCount++;
			// �_�b�V���J�E���g���w��l�ȏ�̏ꍇ�̓_�b�V���I��
			if (nDashCount > 20)
			{
				bDash = false;
				nDashCount = 0;
			}
		}
	}
}


//=============================================================================
// �ړ������֐�
//=============================================================================
void Player::MoveFunc(float fAngle)
{
	m_vMove.x += sinf(fAngle) * m_fMoveSpeed * m_fMoveAccel;
	m_vMove.z += cosf(fAngle) * m_fMoveSpeed * m_fMoveAccel;
}

//=============================================================================
// ��]�����֐�
//=============================================================================
void Player::RotFunc(D3DXVECTOR3 vTag)
{
	D3DXVECTOR3 vecTemp;
	//vecTemp.x = vTag.x - m_vPos.x;
	//vecTemp.z = vTag.z - m_vPos.z;

	vecTemp.x = m_vPos.x - vTag.x;
	vecTemp.z = m_vPos.z - vTag.z;


	// atan2�̃G���[�h�~
	if (vecTemp.x == 0 && vecTemp.z == 0)
	{
		vecTemp.x += 0.00001;
	}

	// �p�x�v�Z
	//m_vRotDest.y = atan2(vecTemp.x, vecTemp.z);
	m_vRot.y = atan2(vecTemp.x, vecTemp.z);

	//
	//// ��]��ƌ��݂̊p�x�����v�Z
	//float fRotDiff;
	//fRotDiff = m_vRotDest.y - m_vRot.y;
	//fRotDiff = PiCalculate180(fRotDiff);

	//// �p�x����K�p
	//m_vRot.y += fRotDiff * 0.02f;
	//m_vRot.y = PiCalculate180(m_vRot.y);

}


//=============================================================================
// ���������֐�
//=============================================================================
void Player::MoveInertia(float fInertia)
{
	m_vMove.x += (0.0f - m_vMove.x) * fInertia;
	m_vMove.y += (0.0f - m_vMove.y) * fInertia;
	m_vMove.z += (0.0f - m_vMove.z) * fInertia;
}

//=============================================================================
// �A�j���[�V�����ݒ�֐�
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
// �R���X�g���N�^�i�����������j
//=============================================================================
//Fireman::Fireman(void)
//{
//
//}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
Fireman::~Fireman(void)
{
}