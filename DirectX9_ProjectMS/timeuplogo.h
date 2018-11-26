//=============================================================================
//
// �v���C���[���� [timeuplogo.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _TIMEUPLOGO_H_
#define _TIMEUPLOGO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_TIMEUPLOGO_000					"data/TEXTURE/timeup001.png"											// gage hp



#define TEXTURE_TIMEUPLOGO_PIXEL000_X				(200)																// �s�N�Z���T�C�Y
#define TEXTURE_TIMEUPLOGO_PIXEL000_Y				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_TIMEUPLOGO_PIXEL001_X				(200)																// �s�N�Z���T�C�Y
#define TEXTURE_TIMEUPLOGO_PIXEL001_Y				(50)																// �s�N�Z���T�C�Y


#define TEXTURE_TIMEUPLOGO_SIZE000_LATE_X			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE000_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE001_LATE_X			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE001_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE002_LATE_X			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE002_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE003_LATE_X			(1.0)																// �g��{��
#define TEXTURE_TIMEUPLOGO_SIZE003_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_TIMEUPLOGO_SCALE_X					(1.0)																// �΂߃T�C�Y
#define TEXTURE_TIMEUPLOGO_SCALE_Y					(1.0)																// �΂߃T�C�Y


#define TEXTURE_TIMEUPLOGO_SIZE000_X				(TEXTURE_TIMEUPLOGO_SIZE000_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_TIMEUPLOGO_PIXEL000_X*1.5)						// �T�C�Y
#define TEXTURE_TIMEUPLOGO_SIZE000_Y				(TEXTURE_TIMEUPLOGO_SIZE000_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_TIMEUPLOGO_PIXEL000_Y*1.5)						// �T�C�Y


#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION001_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION001_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION002_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION002_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION003_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_TIMEUPLOGO_OFFSET_POSITION003_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����


#define TEXTURE_TIMEUPLOGO_POSITION000_X			(TEXTURE_TIMEUPLOGO_OFFSET_POSITION000_X+SCREEN_WIDTH/2)					// �|�W�V����
#define TEXTURE_TIMEUPLOGO_POSITION000_Y			(TEXTURE_TIMEUPLOGO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_TIMEUPLOGO_ANGLE_X				(0.0)																		// �|�W�V����



#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT000_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT000_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT000_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT000_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT001_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT001_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT001_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT001_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT002_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT002_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT002_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT002_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT003_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT003_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT003_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_DEFAULT003_A		(255)																// �e�N�X�`�����_�J���[�ω��O

#define TEXTURE_TIMEUPLOGO_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_SCOND						(3)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TIMEUPLOGO_SCOND_COUNT				(2)
#define TEXTURE_TIMEUPLOGO_SCOND_COUNT_COLOR			(255.0f /TEXTURE_TIMEUPLOGO_SCOND_COUNT)
#define TEXTURE_TIMEUPLOGO_SCOND_TIME				(FRAME*TEXTURE_TIMEUPLOGO_SCOND)									//300
#define TEXTURE_TIMEUPLOGO_SCOND_COLOR				(TEXTURE_TIMEUPLOGO_SCOND_COUNT_COLOR/TEXTURE_TIMEUPLOGO_SCOND_TIME)								//90
#define TEXTURE_TIMEUPLOGO_TIME_000					(FRAME)								//90

#define NUM_TIMEUPLOGO								(1)																// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Timeuplogo : public ObjectManager
{
public:


	struct TimeuplogoParts
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
		int 					Nowselect;
	};
	TimeuplogoParts TimeuplogoObj[NUM_TIMEUPLOGO];
	void SetVertexTimeuplogo(int CreateCount);
	void SetTextureTimeuplogo(int i);
	void TexTimeuplogo(int i, int flag);
	HRESULT MakeVertexTimeuplogo(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Timeuplogo();
	~Timeuplogo();
	void Set(bool bUse);
};


#endif
