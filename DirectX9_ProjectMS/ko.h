//=============================================================================
//
// �v���C���[���� [ko.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _KO_H_
#define _KO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_KO_000					"data/TEXTURE/ko002.png"												// gage hp
#define TEXTURE_KO_001					"data/TEXTURE/ko002.png"										// gage hp



#define TEXTURE_KO_PIXEL000_X				(200)																// �s�N�Z���T�C�Y
#define TEXTURE_KO_PIXEL000_Y				(50)																// �s�N�Z���T�C�Y
#define TEXTURE_KO_PIXEL001_X				(200)																// �s�N�Z���T�C�Y
#define TEXTURE_KO_PIXEL001_Y				(50)																// �s�N�Z���T�C�Y


#define TEXTURE_KO_SIZE000_LATE_X			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE000_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE001_LATE_X			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE001_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE002_LATE_X			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE002_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE003_LATE_X			(1.0)																// �g��{��
#define TEXTURE_KO_SIZE003_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_KO_SCALE_X					(1.0)																// �΂߃T�C�Y
#define TEXTURE_KO_SCALE_Y					(1.0)																// �΂߃T�C�Y


#define TEXTURE_KO_SIZE000_X				(TEXTURE_KO_SIZE000_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL000_X)						// �T�C�Y
#define TEXTURE_KO_SIZE000_Y				(TEXTURE_KO_SIZE000_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL000_Y)						// �T�C�Y
#define TEXTURE_KO_SIZE001_X				(TEXTURE_KO_SIZE001_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL001_X)					// �T�C�Y
#define TEXTURE_KO_SIZE001_Y				(TEXTURE_KO_SIZE001_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL001_Y)						// �T�C�Y
#define TEXTURE_KO_SIZE002_X				(TEXTURE_KO_SIZE002_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL002_X)					// �T�C�Y
#define TEXTURE_KO_SIZE002_Y				(TEXTURE_KO_SIZE002_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL002_Y)						// �T�C�Y
#define TEXTURE_KO_SIZE003_X				(TEXTURE_KO_SIZE002_LATE_X*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL003_X)					// �T�C�Y
#define TEXTURE_KO_SIZE003_Y				(TEXTURE_KO_SIZE002_LATE_Y*SCREEN_WIDTH/SCREEN_HEIGHT*TEXTURE_KO_PIXEL003_Y)						// �T�C�Y

#define TEXTURE_KO_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION001_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION001_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION002_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION002_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION003_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_KO_OFFSET_POSITION003_Y	(0.0f)											// �I�t�Z�b�g�|�W�V����


#define TEXTURE_KO_POSITION000_X			(TEXTURE_KO_OFFSET_POSITION000_X+SCREEN_WIDTH/4)					// �|�W�V����
#define TEXTURE_KO_POSITION000_Y			(TEXTURE_KO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_KO_POSITION001_X			(TEXTURE_KO_OFFSET_POSITION001_X+SCREEN_WIDTH/2+SCREEN_WIDTH/4)	// �|�W�V����
#define TEXTURE_KO_POSITION001_Y			(TEXTURE_KO_OFFSET_POSITION001_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_KO_ANGLE_X				(0.0)																		// �|�W�V����



#define TEXTURE_KO_COLOR_DEFAULT000_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT000_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT000_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT000_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT001_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT001_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT001_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT001_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT002_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT002_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT002_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT002_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT003_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT003_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT003_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_DEFAULT003_A		(255)																// �e�N�X�`�����_�J���[�ω��O

#define TEXTURE_KO_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_SCOND						(3)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_KO_SCOND_COUNT				(2)
#define TEXTURE_KO_SCOND_COUNT_COLOR			(255.0f /TEXTURE_KO_SCOND_COUNT)
#define TEXTURE_KO_SCOND_TIME				(FRAME*TEXTURE_KO_SCOND)									//300
#define TEXTURE_KO_SCOND_COLOR				(TEXTURE_KO_SCOND_COUNT_COLOR/TEXTURE_KO_SCOND_TIME)								//90

#define NUM_KO								(2)																// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Ko : public ObjectManager
{
public:


	struct KoParts
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
	};
	KoParts KoObj[NUM_KO];
	void SetVertexKo(int CreateCount);
	void SetTextureKo(int i);
	HRESULT MakeVertexKo(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Ko();
	~Ko();
};


#endif
