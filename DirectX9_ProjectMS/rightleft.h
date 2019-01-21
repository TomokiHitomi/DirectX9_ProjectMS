//=============================================================================
//
// �v���C���[���� [gage.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _RIGHTLEFT_H_
#define _RIGHTLEFT_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_RIGHTLEFT_000					"data/TEXTURE/left320.png"												// gage hp
#define TEXTURE_RIGHTLEFT_001					"data/TEXTURE/right320.png"										// gage hp



#define TEXTURE_RIGHTLEFT_PIXEL000_X				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL000_Y				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL001_X				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL001_Y				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL002_X				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL002_Y				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL003_X				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_RIGHTLEFT_PIXEL003_Y				(50)																// �s�N�Z���T�C�Y


#define TEXTURE_RIGHTLEFT_SIZE000_LATE_X			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE000_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE001_LATE_X			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE001_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE002_LATE_X			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE002_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE003_LATE_X			(1.0)																// �g��{��
#define TEXTURE_RIGHTLEFT_SIZE003_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_RIGHTLEFT_SCALE_X				(1.0)																// �΂߃T�C�Y
#define TEXTURE_RIGHTLEFT_SCALE_Y				(1.0)																// �΂߃T�C�Y


#define TEXTURE_RIGHTLEFT_SIZE000_X				(TEXTURE_RIGHTLEFT_SIZE000_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL000_X/2*SCREEN_SCALE)						// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE000_Y				(TEXTURE_RIGHTLEFT_SIZE000_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL000_Y/2*SCREEN_SCALE)						// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE001_X				(TEXTURE_RIGHTLEFT_SIZE001_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL001_X/2*SCREEN_SCALE)					// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE001_Y				(TEXTURE_RIGHTLEFT_SIZE001_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL001_Y/2*SCREEN_SCALE)						// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE002_X				(TEXTURE_RIGHTLEFT_SIZE002_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL002_X/2*SCREEN_SCALE)					// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE002_Y				(TEXTURE_RIGHTLEFT_SIZE002_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL002_Y/2*SCREEN_SCALE)						// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE003_X				(TEXTURE_RIGHTLEFT_SIZE002_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL003_X/2*SCREEN_SCALE)					// �T�C�Y
#define TEXTURE_RIGHTLEFT_SIZE003_Y				(TEXTURE_RIGHTLEFT_SIZE002_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_RIGHTLEFT_PIXEL003_Y/2*SCREEN_SCALE)						// �T�C�Y

#define TEXTURE_RIGHTLEFT_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION001_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION001_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION002_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION002_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION003_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_RIGHTLEFT_OFFSET_POSITION003_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����


#define TEXTURE_RIGHTLEFT_POSITION000_X			(TEXTURE_RIGHTLEFT_OFFSET_POSITION000_X+TEXTURE_RIGHTLEFT_SIZE000_X)					// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION000_Y			(TEXTURE_RIGHTLEFT_OFFSET_POSITION000_Y+SCREEN_HEIGHT/3-TEXTURE_RIGHTLEFT_SIZE000_Y)	// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION001_X			(TEXTURE_RIGHTLEFT_OFFSET_POSITION001_X+SCREEN_WIDTH/2-TEXTURE_RIGHTLEFT_SIZE001_X)	// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION001_Y			(TEXTURE_RIGHTLEFT_OFFSET_POSITION001_Y+SCREEN_HEIGHT/3-TEXTURE_RIGHTLEFT_SIZE000_Y)	// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION002_X			(TEXTURE_RIGHTLEFT_OFFSET_POSITION002_X+SCREEN_WIDTH/2+TEXTURE_RIGHTLEFT_SIZE002_X)										// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION002_Y			(TEXTURE_RIGHTLEFT_OFFSET_POSITION002_Y+SCREEN_HEIGHT/3-TEXTURE_RIGHTLEFT_SIZE000_Y)										// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION003_X			(TEXTURE_RIGHTLEFT_OFFSET_POSITION003_X+SCREEN_WIDTH-TEXTURE_RIGHTLEFT_SIZE002_X)										// �|�W�V����
#define TEXTURE_RIGHTLEFT_POSITION003_Y			(TEXTURE_RIGHTLEFT_OFFSET_POSITION003_Y+SCREEN_HEIGHT/3-TEXTURE_RIGHTLEFT_SIZE000_Y)										// �|�W�V����
#define TEXTURE_RIGHTLEFT_ANGLE_X				(0.0)																// �|�W�V����



#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT000_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT000_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT000_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT000_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT001_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT001_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT001_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT001_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT002_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT002_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT002_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT002_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT003_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT003_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT003_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_DEFAULT003_A		(255)																// �e�N�X�`�����_�J���[�ω��O

#define TEXTURE_RIGHTLEFT_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O

// ���L���X�g�J�E���g(s)
#define TEXTURE_RIGHTLEFT_SCOND						(5)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_SCOND_FAST				(2)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_RIGHTLEFT								(4)																// �e�N�X�`���̐�

//#define TEXTURE_RIGHTLEFT_SCOND						(3)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_RIGHTLEFT_SCOND_COUNT				(2)
#define TEXTURE_RIGHTLEFT_SCOND_COUNT_COLOR			(255.0f /TEXTURE_RIGHTLEFT_SCOND_COUNT)
//#define TEXTURE_RIGHTLEFT_SCOND_TIME				(FRAME*TEXTURE_RIGHTLEFT_SCOND)									//300
#define TEXTURE_RIGHTLEFT_SCOND_COLOR				(TEXTURE_RIGHTLEFT_SCOND_COUNT_COLOR)								//90

//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Rightleft : public ObjectManager
{
public:


	struct RightleftParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// �v���C���[�̈ړ���
		VERTEX_2D				vertexWk[NUM_VERTEX];					// ���_���i�[���[�N
		D3DXVECTOR2				TextureSize;
		D3DXVECTOR2				TextureSizeAdd;
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		float					Color;
		bool					Use;									// true:�g�p  false:���g�p
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
		bool					Nowselect;
		int						nScendCount;
	};
	RightleftParts RightleftObj[NUM_RIGHTLEFT];
	void SetVertexRightleft(int CreateCount);
	void SetTextureRightleft(int i);
	HRESULT MakeVertexRightleft(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Rightleft();
	~Rightleft();
	bool Set(int nLR);

	//int m_nScendCount[];
};

enum
{
	RIGHTLEFT_COUNT_NORMAL,
	RIGHTLEFT_COUNT_FAST
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool SetRightLeft(int nLR);
bool SetRightLeftSpeed(int nLR, int nFlag);

#endif
