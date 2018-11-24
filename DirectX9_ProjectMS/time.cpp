//=============================================================================
//
// �X�R�A���� [time.cpp]
//
//=============================================================================
#include "main.h"
#include "time.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//HRESULT MakeVertexTime(void);
//void SetTextureTime(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pD3DTextureTime = NULL;		// �e�N�X�`���ւ̃|���S��
//VERTEX_2D				TimeObj[0].vertexWk[TEXTURE_TIME_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N

Time::Time()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::TIME, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Time::~Time()
{
	Uninit();
}

HRESULT Time::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_TIME_000,				// �t�@�C���̖��O
		&TimeObj[0].pD3DTexture);				// �ǂݍ��ރ������̃|�C���^
	

	TimeObj[0].Pos = D3DXVECTOR3((float)TEXTURE_TIME_POSITION000_X, (float)TEXTURE_TIME_POSITION000_Y, 0.0f);
	TimeObj[0].Timer = TEXTURE_TIME_SECOND * FRAME;

	// ���_���̍쐬
	MakeVertexTime();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Time::Uninit(void)
{
	if (TimeObj[0].pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		TimeObj[0].pD3DTexture->Release();
		TimeObj[0].pD3DTexture = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void Time::Update(void)
{
	// ���t���[�����s����鏈�����L�q����
	TimeObj[0].Timer--;

	SetTextureTime();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Time::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;


	//// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	//// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	//// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����


	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, TimeObj[0].pD3DTexture);

	// �X�R�A
	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, TimeObj[0].vertexWk[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Time::MakeVertexTime(void)
{
	int i;
	float habaX = TEXTURE_TIME_SIZE000_X;	// �����̉���

											// ��������������
	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		TimeObj[0].vertexWk[i][0].vtx.x = -habaX * i + TimeObj[0].Pos.x;
		TimeObj[0].vertexWk[i][0].vtx.y = TimeObj[0].Pos.y;
		TimeObj[0].vertexWk[i][0].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][1].vtx.x = -habaX * i + TimeObj[0].Pos.x + TEXTURE_TIME_SIZE000_X;
		TimeObj[0].vertexWk[i][1].vtx.y = TimeObj[0].Pos.y;
		TimeObj[0].vertexWk[i][1].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][2].vtx.x = -habaX * i + TimeObj[0].Pos.x;
		TimeObj[0].vertexWk[i][2].vtx.y = TimeObj[0].Pos.y + TEXTURE_TIME_SIZE000_Y;
		TimeObj[0].vertexWk[i][2].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][3].vtx.x = -habaX * i + TimeObj[0].Pos.x + TEXTURE_TIME_SIZE000_X;
		TimeObj[0].vertexWk[i][3].vtx.y = TimeObj[0].Pos.y + TEXTURE_TIME_SIZE000_Y;
		TimeObj[0].vertexWk[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		TimeObj[0].vertexWk[i][0].rhw = 1.0f;
		TimeObj[0].vertexWk[i][1].rhw = 1.0f;
		TimeObj[0].vertexWk[i][2].rhw = 1.0f;
		TimeObj[0].vertexWk[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		TimeObj[0].vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		TimeObj[0].vertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		TimeObj[0].vertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		TimeObj[0].vertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		TimeObj[0].vertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void Time::SetTextureTime(void)
{
	int i;
	int number = TimeObj[0].Timer / FRAME;

	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		TimeObj[0].vertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		TimeObj[0].vertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		TimeObj[0].vertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		TimeObj[0].vertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// HP�f�[�^���Z�b�g����
// ����:add :�ǉ�����_���B�}�C�i�X���\�A�������ȂǂɁB
//=============================================================================
//void AddTime(int add)
//{
//	TimeObj[0].Time += add;
//	if (g_nTime > TIME_MAX)
//	{
//		g_nTime = TIME_MAX;
//	}
//	else if (g_nTime < 0)
//	{
//
//		g_nTime = 0;
//	}
//
//}
