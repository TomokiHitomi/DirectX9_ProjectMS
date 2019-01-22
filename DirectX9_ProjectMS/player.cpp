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
#include "plane.h"
#include "rightleft.h"
#include "game.h"
#include "scene.h"

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
Player* PlayerManager::m_pPlayer[PlayerManager::PLAYER_MAX];

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
		// �v���C���[��������
		m_pPlayer[i] = NULL;
		// �I���L�������V�[���}�l�[�W���[����擾
		int eTemp = SceneManager::GetSelectChar(i);
		// �I���L�����ɉ����ăL�����N�^�[���Z�b�g
		switch ((CharacterManager::TYPE)eTemp)
		{
		case CharacterManager::FIREMAN:
			Set<Fireman>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::PASTRY:
			Set<Pastry>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::IDOL:
			Set<Idol>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		case CharacterManager::DOCTOR:
			Set<Doctor>((PLAYER)i, (CharacterManager::TYPE)eTemp);
			break;
		}
	}

	//Set<Idol>(PLAYER_2P, CharacterManager::IDOL);
	//Set<Idol>(PLAYER_1P, CharacterManager::IDOL);
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
#ifdef _DEBUG
	// imgui�̍X�V�J�n
	ImGui::Begin("Player");
#endif
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
#ifdef _DEBUG
	// imgui�̍X�V�I��
	ImGui::End();
#endif
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
// ���Z�b�g����
//=============================================================================
void PlayerManager::Reset(void)
{
	for (unsigned int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->eLRSp != Player::TYPE_TEMP)
			{
				// �E�F�|����������
				m_pPlayer[i]->RestoreWeaponSp();
			}
			// �X�e�[�^�X�̏�����
			m_pPlayer[i]->InitStatus();
			// ���W�̏�����
			m_pPlayer[i]->InitPos();
			// �Q�[�W�̏�����
			// �\����A�ǂ��炩�̃Q�[�W������������Ηǂ����񂵂Ă���
			m_pPlayer[i]->pGage->InitStatus();
			m_pPlayer[i]->pGage3d->InitStatus();
		}
	}
}



//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
Player::Player(void)
{
	// �X�L�����b�V���|�C���^�� NULL �ɏ�����
	m_CSkinMesh = NULL;

	// �X�e�[�^�X������
	InitStatus();

	// �E�F�|���̐����� NULL �ɏ�����
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		pWeapon[i] = NULL;
	}

	// �Q�[�W�̃|�C���^��������
	pGage = NULL;
	pGage3d = NULL;
}

//=============================================================================
// �X�e�[�^�X����������
//=============================================================================
void Player::InitStatus(void)
{
	// �e�v���p�e�B�̏�����
	m_vPos = ZERO_D3DXVECTOR3;
	m_vRot = ZERO_D3DXVECTOR3;
	//m_vScl = D3DXVECTOR3(PLAYER_SCL, PLAYER_SCL, PLAYER_SCL);

	m_vMove = ZERO_D3DXVECTOR3;
	m_vRotInertia = ZERO_D3DXVECTOR3;
	m_vRotDiff = ZERO_D3DXVECTOR3;
	m_vRotDistance = ZERO_D3DXVECTOR3;
	m_vRotDest = ZERO_D3DXVECTOR3;
	m_fMoveInertia = 0.3f;

	// �Q�[�W�ݒu���W
	m_vPosGage = ZERO_D3DXVECTOR3;

	// �X�e�[�^�X
	m_fHp = PLAYER_HP_MAX;
	m_fSp = 0;
	m_bSpMax = false;
	m_bSpStandby = false;
	m_bSpMode = false;

	// �N�[���_�E���l
	m_nCoolDown = 0;

	m_nSpLR = 0;
	m_nSpCount = 0;
	m_nSpFlag = false;

	// �e�t���O�ƃE�H�[���A�b�v�E�N�[���_�E���̏�����
	for (unsigned int i = 0; i < AC_MAX; i++)
	{
		m_stAction[i].nCnt = 0;
		m_stAction[i].bFlag = false;
		m_stAction[i].bUse = false;
	}

	// �W�����v
	fVelocity = PLAYER_VELOCITY;
	fGravity = PLAYER_GRAVITY;
	bJump = false;

	// �_�b�V��
	vDash = ZERO_D3DXVECTOR3;			// �ړ��ʏ��
	nDashCount = 0;
	bDash = false;

	// �K�[�h
	m_fGuardHp = PLAYER_GUARD_HP_MAX;	// �ϋv�l��ݒ�

	m_fMoveSpeed = PLAYER_MOVE_SPEED;
	m_fRiseSpeed = 0.0f;
	m_bUse = true;

	// SP�A�^�b�N�p TEMP �ŏ�����
	eLRSp = TYPE_TEMP;

	ChangeAnim(IDOL, PLAYER_ANIM_WEIGHT_MAX);

	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
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
#ifdef _DEBUG
	//PrintDebugProc("Player[%d]  Hp[%f]  GHp[%f]\n", m_nNum, m_fHp, m_fGuardHp);
	ImGui::Text("Player[%d]  Hp[%f]  GHp[%f]\n", m_nNum, m_fHp, m_fGuardHp);
	//if (ImGui::Button("SpMode = true"))
	//{
	//	m_bSpMode = true;
	//}
#endif

	if (m_bUse)
	{
		// �Q�[�W�̃|�C���^�� NUUL �Ȃ�擾
		if (pGage == NULL)
			pGage = ObjectManager::GetObjectPointer<Gage>(ObjectManager::GAGE);
		if (pGage3d == NULL)
			pGage3d = ObjectManager::GetObjectPointer<Gage3d>(ObjectManager::GAGE3D);

		if (GameScene::GetGameFlag())
		{
			// �s������
			Action();

			// �N�[���_�E������
			ActionCD();

			// �ړ�����
			Move();

			if (m_fHp <= 0.0f)
				m_dwAnim |= PLAYER_ANIM_DOWN;

			// �A�j���[�V������ݒ�
			SetAnim();

			// SP�̎����`���[�W
			AddSp(PLAYER_SP_CHARGE_AUTO);
		}

		if (m_CSkinMesh != NULL)
		{
			// ���f�����X�V
			m_CSkinMesh->Update(m_nNum);
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
		//// SP�̎����`���[�W
		//AddSp(PLAYER_SP_CHARGE_AUTO);

		// �ړ���������
		MoveLimit();

		//// �ړ��ʂ����W�ɔ��f
		//m_vPos += m_vMove;

		//D3DXVECTOR3 vTag = pCube->GetPos();


		// �A�^�b�N�t���O�������Ă��Ȃ�������
		if (!m_stAction[AC_ATTACK].bFlag)
		{
			// ��]����
			RotFunc(m_vTag);
		}

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


		// �Q�[�W�ݒu���W�̎Z�o
		m_vPosGage = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
		D3DXVec3Normalize(&m_vPosGage, &m_vPosGage);

		// �Q�[�W�ݒu�ꏊ�𒲐����ăv���C���[Pos�ɃI�t�Z�b�g
		m_vPosGage.x = m_vPos.x + m_vPosGage.x * PLAYER_GAGE_SET_XZ;
		m_vPosGage.z = m_vPos.z + m_vPosGage.z * PLAYER_GAGE_SET_XZ;
		m_vPosGage.y = m_vPos.y + PLAYER_GAGE_HEIGHT;





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

		// ���[���h�ϊ�
		WorldConvertXYZ(&m_mtxWorld, m_vPos, m_vRot, m_vScl);

		if (m_CSkinMesh != NULL)
		{
			if(CameraManager::GetType() == CameraManager::MULTI2) m_CSkinMesh->StopAnim();
			// ���f����`��
			m_CSkinMesh->Draw(pDevice, m_mtxWorld, m_nNum);
			m_CSkinMesh->PlayAnim();
		}
	}
}

//=============================================================================
// �s������
//=============================================================================
void Player::Action(void)
{
	// �ړ��ʂ�������
	m_vMove = ZERO_D3DXVECTOR3;

	// �A�j���[�V�����r�b�g�p�^�[����������
	m_dwAnim = 0x00000000l;	// ������

	// �_���[�W����
	Damage();

	// Sp���Z����
	SubSp(PLAYER_SP_SUB);

	

	if (CheckJoyconSize(4) || (CheckJoyconSize(2) && m_nNum == 0))
	{
		D3DXVECTOR3 jcL, jcR;
		jcL = GetJoyconAccel(0 + m_nNum * 2);
		jcR = GetJoyconAccel(1 + m_nNum * 2);

		// �A�^�b�N����
		if (jcL.y > PLAYER_MARGIN_ATTACK)
		{
			// �E�F�|��������ɃZ�b�g����Ă�����
			if (pWeapon[TYPE_LEFT])
			{
				// �A�^�b�N�����s
				Attack(TYPE_LEFT);
			}
		}
		if (jcR.y > PLAYER_MARGIN_ATTACK)
		{
			// �E�F�|��������ɃZ�b�g����Ă�����
			if (pWeapon[TYPE_RIGHT])
			{
				// �A�^�b�N�����s
				Attack(TYPE_RIGHT);
			}
		}

		// �A�^�b�N�t���O�������Ă���΃A�j���[�V�����r�b�g�𗧂Ă�
		if (m_stAction[AC_ATTACK_LEFT].bFlag) m_dwAnim |= PLAYER_ANIM_ATK_LEFT;
		else if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_dwAnim |= PLAYER_ANIM_ATK_RIGHT;

		// �K�[�h���łȂ����
		if (!m_stAction[AC_GURAD_WU].bFlag)
		{
			// �E�F�|�������u����
			pWeapon[TYPE_LEFT]->Remote(jcL.z);
			pWeapon[TYPE_RIGHT]->Remote(jcR.z);
		}

		if (!m_stAction[AC_ATTACK].bFlag)
		{
			// �K�[�h����
			if (jcL.z < -PLAYER_MARGIN_GUARD && jcR.z > PLAYER_MARGIN_GUARD)
			{
				Guard();
			}
			else
			{
				// �K�[�h�t���O�� false
				m_stAction[AC_GURAD_WU].bUse = false;
			}
		}

		// �A�^�b�N�E�K�[�h���łȂ����
		if(!m_stAction[AC_GURAD_WU].bUse && !m_stAction[AC_GURAD_CD].bFlag && !m_stAction[AC_ATTACK].bFlag)
		{
			// �K�[�h�̑ϋv�l��
			m_fGuardHp += PLAYER_GUARD_HP_RECOVER;
			if (m_fGuardHp > PLAYER_GUARD_HP_MAX) m_fGuardHp = PLAYER_GUARD_HP_MAX;

			// �ړ�
			bool bMove = false;
			float fMoveAccel = 0.0f;
			// �O
			if (jcL.y > PLAYER_MARGIN_MOVE && jcR.y > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				fMoveAccel = m_fMoveAccel;
				MoveFunc(m_vRot.y + D3DX_PI);
				m_dwAnim |= PLAYER_ANIM_FRONT;
			}
			// ��
			else if (jcL.y < -PLAYER_MARGIN_MOVE && jcR.y < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.y, jcR.y);
				fMoveAccel = m_fMoveAccel;
				MoveFunc(m_vRot.y);
				m_dwAnim |= PLAYER_ANIM_BACK;
			}
			// ��
			if (jcL.z > PLAYER_MARGIN_MOVE && jcR.z > PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y + D3DX_PI * 0.50f);
				if (fMoveAccel < m_fMoveAccel)
				{
					m_dwAnim |= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim ^= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim |= PLAYER_ANIM_LEFT;
				}
			}
			// �E
			else if (jcL.z < -PLAYER_MARGIN_MOVE && jcR.z < -PLAYER_MARGIN_MOVE)
			{
				m_fMoveAccel = CompHigh(jcL.z, jcR.z);
				MoveFunc(m_vRot.y - D3DX_PI * 0.50f);
				if (fMoveAccel < m_fMoveAccel)
				{
					m_dwAnim |= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim ^= PLAYER_ANIM_FRONT | PLAYER_ANIM_BACK;
					m_dwAnim |= PLAYER_ANIM_RIGHT;
				}
			}

			if (!bJump)
			{
				// �W�����v
				if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_R))
				{
				// �J�E���g�J�n
				m_stAction[AC_JUMP_CD].bFlag = true;
				// �J�E���g�l��ݒ�
				m_stAction[AC_JUMP_CD].nCnt = PLAYER_JUMP_CD;
				bJump = true;

				}
			}

			if (!bDash)
			{
				// �_�b�V��
				if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_L))
				{
					bDash = true;
					SetSe(SE_DASH, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
				}
			}
		}
		// SP�A�^�b�N����
		ChangeWeaponSp();
	}
	// Joycon�̐ڑ����Ȃ������ꍇ�̓L�[�{�[�h����i�ړ��̂݁j
	else
	{
		ActionKeyboard();
	}
	AttackUpdate();
	Dash();
	Jump();
} 

//=============================================================================
// �s�������i�L�[�{�[�h�j
//=============================================================================
void Player::ActionKeyboard(void)
{
	if (m_nNum == 0)
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
}

//=============================================================================
// �ړ�����
//=============================================================================
void Player::Move(void)
{
	m_vPos += m_vMove;
}

//=============================================================================
// �N�[���_�E������
//=============================================================================
void Player::ActionCD(void)
{
	for (unsigned int i = 0; i < AC_MAX; i++)
	{
		// �t���O�� true �Ȃ��
		if (m_stAction[i].bFlag)
		{
			// �N�[���_�E�������Z
			m_stAction[i].nCnt--;
			// 0�����������
			if(m_stAction[i].nCnt < 0)
			{
				// �t���O�� false
				m_stAction[i].bFlag = false;
				// �g�p�t���O�� true
				m_stAction[i].bUse = true;
			}
		}
	}
}

//=============================================================================
// �_���[�W����
//=============================================================================
void Player::Damage(void)
{
	// �_���[�W�t���O�� true �Ȃ��
	if (m_stAction[AC_DAMAGE].bFlag)
	{
		// �_���[�W�P�̃A�j���[�V�����t���O�𗧂Ă�
		m_dwAnim |= PLAYER_ANIM_DAMAGE_1;
	}
}

//=============================================================================
// �A�^�b�N�����֐�
//=============================================================================
void Player::Attack(WeaponLR eLR)
{
	// �ݒu�\��Ԃł����
	if (SetRightLeft((int)eLR + m_nNum * 2))
	{
		if (m_bSpMode)
		{
			SetSe(SE_DOCTOR_THROW, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);


			if (eLR == TYPE_LEFT)
			{
				// RIGHT �̃t���O�������Ă����� false �ɂ���
				if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_stAction[AC_ATTACK_RIGHT].bFlag = false;
				// �t���O�𗧂Ă�
				m_stAction[AC_ATTACK_LEFT].bFlag = true;
				// �N�[���_�E���l����
				m_stAction[AC_ATTACK_LEFT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}
			else if (eLR == TYPE_RIGHT)
			{
				// LEFT �̃t���O�������Ă����� false �ɂ���
				if (m_stAction[AC_ATTACK_LEFT].bFlag)m_stAction[AC_ATTACK_LEFT].bFlag = false;
				// �t���O�𗧂Ă�
				m_stAction[AC_ATTACK_RIGHT].bFlag = true;
				// �N�[���_�E���l����
				m_stAction[AC_ATTACK_RIGHT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}

			// �t���O�𗧂Ă�
			m_stAction[AC_ATTACK].bFlag = true;
			// �N�[���_�E���l����
			m_stAction[AC_ATTACK].nCnt = PLAYER_ATTACK_CD;

			// �ݒu���W�̎Z�o
			D3DXVECTOR3 posTmp = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
			D3DXVec3Normalize(&posTmp, &posTmp);

			// RIGHT �̏ꍇ�͐ݒupos�����Α�
			if (eLR == TYPE_RIGHT)posTmp *= -1.0f;

			// �ݒu�ꏊ�𒲐����ăv���C���[Pos�ɃI�t�Z�b�g
			posTmp.x = m_vPos.x + posTmp.x * PLAYER_WEAPON_SET_XZ;
			posTmp.z = m_vPos.z + posTmp.z * PLAYER_WEAPON_SET_XZ;
			posTmp.y = m_vPos.y + PLAYER_WEAPON_SET_HEIGHT;

			// �ړ��x�N�g���̎Z�o
			D3DXVECTOR3 moveTmp = m_vTag;
			moveTmp.y += PLAYER_HEIGHT_HIT;
			moveTmp = moveTmp - posTmp;
			D3DXVec3Normalize(&moveTmp, &moveTmp);

			// �E�F�|�����Z�b�g
			pWeapon[eLR]->Set(posTmp, moveTmp);

			// Joycon�U��
			JcRumble((int)eLR + m_nNum * 2, 99, 1);

		}
		else
		{
			if (m_nSpCount <= PLAYER_ATTACK_START && m_nSpFlag)
			{
				m_nSpLR = (int)TYPE_SP;
			}
			else
			{
				m_nSpLR = (int)eLR;
			}
			m_nSpFlag = true;
		}
	}


}

//=============================================================================
// �A�^�b�N�����֐�
//=============================================================================
void Player::AttackUpdate(void)
{
	if (!m_bSpMode)
	{
		if (m_nSpFlag)
		{
			m_nSpCount++;
		}

		if (m_nSpCount > PLAYER_ATTACK_START)
		{
			m_nSpCount = 0;
			m_nSpFlag = false;

			// SP�`���[�W
			AddSp(PLAYER_SP_CHARGE_ATTACK);

			//// SP�A�^�b�N�������ς�
			//if (m_bSpStandby)
			//{
			//	// Sp��������
			//	ResetSp();
			//	// �X�^���o�C�t���O�� false
			//	m_bSpStandby = false;
			//}
			//else if (eLRSp != TYPE_TEMP)
			//{
			//	// �E�F�|����������
			//	RestoreWeaponSp();
			//}
			//else
			SetSe(SE_DOCTOR_THROW, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);


			if (m_nSpLR == TYPE_LEFT || m_nSpLR == TYPE_SP)
			{
				// RIGHT �̃t���O�������Ă����� false �ɂ���
				if (m_stAction[AC_ATTACK_RIGHT].bFlag)m_stAction[AC_ATTACK_RIGHT].bFlag = false;
				// �t���O�𗧂Ă�
				m_stAction[AC_ATTACK_LEFT].bFlag = true;
				// �N�[���_�E���l����
				m_stAction[AC_ATTACK_LEFT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}
			else if (m_nSpLR == TYPE_RIGHT)
			{
				// LEFT �̃t���O�������Ă����� false �ɂ���
				if (m_stAction[AC_ATTACK_LEFT].bFlag)m_stAction[AC_ATTACK_LEFT].bFlag = false;
				// �t���O�𗧂Ă�
				m_stAction[AC_ATTACK_RIGHT].bFlag = true;
				// �N�[���_�E���l����
				m_stAction[AC_ATTACK_RIGHT].nCnt = PLAYER_ATTACK_CD_ANIM;
			}

			// �t���O�𗧂Ă�
			m_stAction[AC_ATTACK].bFlag = true;
			// �N�[���_�E���l����
			m_stAction[AC_ATTACK].nCnt = PLAYER_ATTACK_CD;

			// �ݒu���W�̎Z�o
			D3DXVECTOR3 posTmp = D3DXVECTOR3(m_mtxWorld._11, m_mtxWorld._12, m_mtxWorld._13);
			D3DXVec3Normalize(&posTmp, &posTmp);

			// RIGHT �̏ꍇ�͐ݒupos�����Α�
			if (m_nSpLR == TYPE_RIGHT)posTmp *= -1.0f;

			// �ݒu�ꏊ�𒲐����ăv���C���[Pos�ɃI�t�Z�b�g
			posTmp.x = m_vPos.x + posTmp.x * PLAYER_WEAPON_SET_XZ;
			posTmp.z = m_vPos.z + posTmp.z * PLAYER_WEAPON_SET_XZ;
			posTmp.y = m_vPos.y + PLAYER_WEAPON_SET_HEIGHT;

			// �ړ��x�N�g���̎Z�o
			D3DXVECTOR3 moveTmp = m_vTag;
			moveTmp.y += PLAYER_HEIGHT_HIT;
			moveTmp = moveTmp - posTmp;
			D3DXVec3Normalize(&moveTmp, &moveTmp);

			// �E�F�|�����Z�b�g
			pWeapon[m_nSpLR]->Set(posTmp, moveTmp);

			// Joycon�U��
			if (m_nSpLR == TYPE_SP)
			{
				JcRumble((int)0 + m_nNum * 2, 99, 1);
				JcRumble((int)1 + m_nNum * 2, 99, 1);
			}
			else
			{				
				JcRumble((int)m_nSpLR + m_nNum * 2, 99, 1);
			}
		}
	}
}


//=============================================================================
// SP�E�F�|���ύX����
//=============================================================================
void Player::ChangeWeaponSp(void)
{
	// Sp���ő�l�̏ꍇ
	if (m_bSpMax)
	{
		// Joycon��
		if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_ZL)
			|| JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_ZR))
		{
			m_bSpMax = false;
			m_bSpMode = true;
			SetSe(SE_ATKSP, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
		}
	}

	//if (m_bSpMax && !m_bSpStandby)
	//{
	//	// Joycon��
	//	if (JcTriggered(0 + m_nNum * 2, JC_L_BUTTON_ZL))
	//	{
	//		// LEFT�̃|�C���^���e���|�����ɕۊ�
	//		pWeapon[Player::TYPE_TEMP] = pWeapon[Player::TYPE_LEFT];
	//		// LEFT��SP��ڑ�
	//		pWeapon[Player::TYPE_LEFT] = pWeapon[Player::TYPE_SP];
	//		// �ڑ�����i�[
	//		eLRSp = TYPE_LEFT;
	//		// �X�^���o�C�t���O�� true
	//		m_bSpStandby = true;
	//	}
	//	else if (JcTriggered(1 + m_nNum * 2, JC_R_BUTTON_ZR))
	//	{
	//		// RIGHT�̃|�C���^���e���|�����ɕۊ�
	//		pWeapon[Player::TYPE_TEMP] = pWeapon[Player::TYPE_RIGHT];
	//		// RIGHT��SP��ڑ�
	//		pWeapon[Player::TYPE_RIGHT] = pWeapon[Player::TYPE_SP];
	//		// �ڑ�����i�[
	//		eLRSp = TYPE_RIGHT;
	//		// �X�^���o�C�t���O�� true
	//		m_bSpStandby = true;
	//	}
	//}
	
}

//=============================================================================
// �E�F�|����������
//=============================================================================
void Player::RestoreWeaponSp(void)
{
	// �E�F�|���̃|�C���^�𕜌�����
	pWeapon[eLRSp] = pWeapon[Player::TYPE_TEMP];
	// �t���O�� TEMP �ɖ߂�
	eLRSp = TYPE_TEMP;
}

//=============================================================================
// SP���Z����
//=============================================================================
void Player::AddSp(float fSp)
{
	if (!m_bSpMode)
	{
		m_fSp += fSp;
		pGage->SkillAdd(fSp, m_nNum);
		pGage3d->SkillAdd(fSp, m_nNum);
		if (m_fSp >= PLAYER_SP_MAX)
		{
			m_fSp = PLAYER_SP_MAX;
			if (!m_bSpMax)
				SetSe(SE_SP_MAX, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
			m_bSpMax = true;
			return;
		}
		m_bSpMax = false;
	}
}

//=============================================================================
// SP���Z����
//=============================================================================
void Player::SubSp(float fSp)
{
	if (m_bSpMode)
	{
		SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
		SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);

		m_fSp -= fSp;
		pGage->SkillReduce(fSp, m_nNum);
		pGage3d->SkillReduce(fSp, m_nNum);
		if (m_fSp < 0)
		{
			m_fSp = 0;
			if (m_bSpMode)
				SetSe(SE_SP_MAX, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
			m_bSpMode = false;
			SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
			SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);

			return;
		}
	}

	//if (GetKeyboardTrigger(DIK_Z))
	//{
	//	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	//	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_NORMAL);
	//}
	//else if (GetKeyboardTrigger(DIK_X))
	//{
	//	SetRightLeftSpeed(0 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
	//	SetRightLeftSpeed(1 + m_nNum * 2, RIGHTLEFT_COUNT_FAST);
	//}
	//m_bSpMax = false;
}

//=============================================================================
// SP���Z�b�g
//=============================================================================
void Player::ResetSp(void)
{
	m_fSp = 0.0f;
	pGage->SkillReduce(PLAYER_SP_MAX, m_nNum);
	pGage3d->SkillReduce(PLAYER_SP_MAX, m_nNum);
}

//=============================================================================
// HP���Z����
//=============================================================================
bool Player::SubHp(float fDamage)
{
	m_fHp -= fDamage;
	// �^�[�Q�b�g�̃Q�[�WHP�����Z
	pGage->DamegeReduce(fDamage, m_nNum);
	pGage3d->DamegeReduce(fDamage, m_nNum);
	if (m_fHp <= 0.0f) return true;
	return false;
}

//=============================================================================
// �K�[�hHP���Z����
//=============================================================================
bool Player::SubHpGuard(float fDamage)
{
	m_fGuardHp -= fDamage;
	if (m_fGuardHp < 0.0f)
	{
		m_fGuardHp = 0.0f;
		return true;
	}
	return false;
}

//=============================================================================
// �_���[�W�N�[���_�E���ݒ菈��
//=============================================================================
void Player::SetDamage(void)
{
	m_stAction[AC_DAMAGE].bFlag = true;
	m_stAction[AC_DAMAGE].nCnt = PLAYER_DAMAGE_CD;
}


//=============================================================================
// �K�[�h�����֐�
//=============================================================================
void Player::Guard(void)
{
	// �K�[�h�t���O�ƃJ�E���g�t���O�� false �Ȃ��
	if (!m_stAction[AC_GURAD_WU].bUse && !m_stAction[AC_GURAD_WU].bFlag)
	{
		// �J�E���g�J�n
		m_stAction[AC_GURAD_WU].bFlag = true;
		// �J�E���g�l��ݒ�
		m_stAction[AC_GURAD_WU].nCnt = PLAYER_GUARD_COUNT;
	}

	// �g�p�t���O�� true �Ȃ��
	if (m_stAction[AC_GURAD_WU].bUse)
	{
		// �K�[�h�A�j���[�V�������Z�b�g
		m_dwAnim |= PLAYER_ANIM_GUARD;
		// �_�b�V�����L�����Z��
		DashCancel();

		// �t���O�𗧂Ă�
		m_stAction[AC_GURAD_CD].bFlag = true;
		// �N�[���_�E���l����
		m_stAction[AC_GURAD_CD].nCnt = PLAYER_GUARD_CD;
	}
}


//=============================================================================
// �W�����v�����֐�
//=============================================================================
void Player::Jump(void)
{
	// �W�����v��
	if (bJump)
	{
		//// �W�����v�N�[���_�E���t���O�� true
		//if (m_stAction[AC_JUMP_CD].bFlag)
		//{
			// �W�����v�X�^�[�g�A�j���[�V�������Z�b�g
			m_dwAnim |= PLAYER_ANIM_JUMP_START;
		//}
		//else
		//{
		//	// �W�����v�X�^�[�g�A�j���[�V�������Z�b�g
		//	m_dwAnim |= PLAYER_ANIM_JUMP;
		//}

		fVelocity -= fGravity;
		m_vPos.y += fVelocity;
		if (m_vPos.y <= 0.0f)
		{
			//// �J�E���g�J�n
			//m_stAction[AC_JUMP_END_CD].bFlag = true;
			//// �J�E���g�l��ݒ�
			//m_stAction[AC_JUMP_END_CD].nCnt = PLAYER_JUMP_CD;

			m_vPos.y = 0.0f;
			fVelocity = PLAYER_VELOCITY;
			fGravity = PLAYER_GRAVITY;
			bJump = false;
			//m_dwAnim |= PLAYER_ANIM_JUMP_END;
		}
	}
//	if(m_stAction[AC_JUMP_END_CD].bFlag)
//		m_dwAnim |= PLAYER_ANIM_JUMP_END;
}

//=============================================================================
// �_�b�V���L�����Z�������֐�
//=============================================================================
void Player::DashCancel(void)
{
	bDash = false;
	nDashCount = 0;
}

//=============================================================================
// �_�b�V�������֐�
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
			m_vMove *= PLAYER_DASH_SPEED;
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
			if (nDashCount > PLAYER_DASH_TIME)
			{
				bDash = false;
				nDashCount = 0;
			}
		}
		ChangeAnimSpeed(PLAYER_ANIM_SPEED_DASH);
	}
	else
	{
		ChangeAnimSpeed(PLAYER_ANIM_SPEED_DEF);
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
	D3DXVECTOR3		vecTemp;
	float			fRotTemp;
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
	fRotTemp = atan2(vecTemp.x, vecTemp.z);

	//
	//// ��]��ƌ��݂̊p�x�����v�Z
	//float fRotDiff;
	//fRotDiff = m_vRotDest.y - m_vRot.y;

	fRotTemp -= m_vRot.y;
	fRotTemp = PiCalculate180(fRotTemp);


	m_vRot.y += fRotTemp * PLAYER_ROT_INERTIA;

	//// �p�x����K�p
	//m_vRot.y += fRotDiff * 0.02f;
	m_vRot.y = PiCalculate180(m_vRot.y);

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
// �A�j���[�V�����ύX�֐�
//=============================================================================
void Player::ChangeAnim(DWORD dwAnime, FLOAT fShift)
{
	if (m_CSkinMesh != NULL)
	{
		m_CSkinMesh->ChangeAnim(dwAnime, fShift, m_nNum);
	}
}

//=============================================================================
// �A�j���[�V�����X�s�[�h�ݒ�֐�
//=============================================================================
void Player::ChangeAnimSpeed(FLOAT AnimSpeed)
{
	if (m_CSkinMesh != NULL)
	{
		m_CSkinMesh->SetAnimSpeed(AnimSpeed, m_nNum);
	}
}

//=============================================================================
// �A�j���[�V�����ݒ�֐�
//=============================================================================
void Player::SetAnim(void)
{
	// �D�揇�ʂ��Ƃ� if ����
	if (PLAYER_ANIM_DUMMY & m_dwAnim);
	else if (PLAYER_ANIM_DOWN & m_dwAnim)
		ChangeAnim(DOWN, PLAYER_ANIM_WEIGHT_DAMAGE);
	else if (PLAYER_ANIM_DAMAGE_1 & m_dwAnim)
	{
		ChangeAnim(DAMAGE_1, PLAYER_ANIM_WEIGHT_DAMAGE);
	}
	else if (PLAYER_ANIM_GUARD & m_dwAnim)
	{
		ChangeAnim(GUARD_CON, PLAYER_ANIM_WEIGHT_GUARD);
	}
	else if (PLAYER_ANIM_ATK_RIGHT & m_dwAnim)
	{
		ChangeAnim(ATK_RIGHT, PLAYER_ANIM_WEIGHT_ATTACK);
	}
	else if (PLAYER_ANIM_ATK_LEFT & m_dwAnim)
	{
		ChangeAnim(ATK_LEFT, PLAYER_ANIM_WEIGHT_ATTACK);
	}
	else if (PLAYER_ANIM_JUMP_END & m_dwAnim)
	{
		ChangeAnim(JUMP_END, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_JUMP & m_dwAnim)
	{
		ChangeAnim(JUMP, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_JUMP_START & m_dwAnim)
	{
		ChangeAnim(JUMP_START, PLAYER_ANIM_WEIGHT_JUMP);
	}
	else if (PLAYER_ANIM_FRONT & m_dwAnim)
	{
		ChangeAnim(FRONT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_BACK & m_dwAnim)
	{
		ChangeAnim(BACK, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_LEFT & m_dwAnim)
	{
		ChangeAnim(LEFT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else if (PLAYER_ANIM_RIGHT & m_dwAnim)
	{
		ChangeAnim(RIGHT, PLAYER_ANIM_WEIGHT_DEF);
	}
	else
	{
		ChangeAnim(IDOL, PLAYER_ANIM_WEIGHT_DEF);
	}
}

//=============================================================================
// �ړ���������
//=============================================================================
void Player::MoveLimit(void)
{
	float fLimit;
	fLimit = PLANE_SIZE_X * PLANE_X_MAX;
	if (m_vPos.x > fLimit) m_vPos.x = fLimit;
	if (m_vPos.x < -fLimit)m_vPos.x = -fLimit;

	fLimit = PLANE_SIZE_Y * PLANE_Y_MAX;
	if (m_vPos.z > fLimit) m_vPos.z = fLimit;
	if (m_vPos.z < -fLimit)m_vPos.z = -fLimit;
}

//=============================================================================
// ���W����������
//=============================================================================
void Player::InitPos(void)
{
	if (m_nNum == 0)m_vPos = PLAYER_POS;
	else m_vPos = PLAYER_POS * -1.0f;
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