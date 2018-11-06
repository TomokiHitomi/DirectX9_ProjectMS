//=============================================================================
//
// �v���C���[���� [gage.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_GAGE_000					"data/TEXTURE/gage000.png"											// ���S
#define TEXTURE_GAGE_001					"data/TEXTURE/gage000.png"											// ���S
#define TEXTURE_GAGE_002					"data/TEXTURE/gage000.png"											// ���S
#define TEXTURE_GAGE_003					"data/TEXTURE/gage000.png"											// ���S
#define TEXTURE_GAGE_004					"data/TEXTURE/gage000.png"											// ���S
#define TEXTURE_GAGE_005					"data/TEXTURE/gage000.png"											// ���S

#define TEXTURE_GAGE_PIXEL000_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL000_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL001_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL001_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL002_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL002_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL003_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL003_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL004_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL004_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL005_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL005_Y				(1000)																// �s�N�Z���T�C�Y


#define TEXTURE_GAGE_SIZE000_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE000_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE001_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE001_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE002_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE002_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE003_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE003_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE004_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE004_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE005_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE005_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_GAGE_SIZEADD_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/4)						// �΂߃T�C�Y
#define TEXTURE_GAGE_SIZEADD_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �΂߃T�C�Y

#define TEXTURE_GAGE_SIZE000_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE000_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE001_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE001_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE002_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE002_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE003_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE003_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE004_X				(TEXTURE_GAGE_SIZE004_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE004_Y				(TEXTURE_GAGE_SIZE004_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE005_X				(TEXTURE_GAGE_SIZE005_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GAGE_SIZE005_Y				(TEXTURE_GAGE_SIZE005_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y

#define TEXTURE_GAGE_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION001_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION001_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION002_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION002_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION003_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION003_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION004_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION004_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION005_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION005_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����


#define TEXTURE_GAGE_POSITION000_X			(TEXTURE_GAGE_OFFSET_POSITION000_X+SCREEN_WIDTH/4)					// �|�W�V����
#define TEXTURE_GAGE_POSITION000_Y			(TEXTURE_GAGE_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// �|�W�V����
#define TEXTURE_GAGE_POSITION001_X			(TEXTURE_GAGE_OFFSET_POSITION001_X+SCREEN_WIDTH/2+SCREEN_WIDTH/4)	// �|�W�V����
#define TEXTURE_GAGE_POSITION001_Y			(TEXTURE_GAGE_OFFSET_POSITION001_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// �|�W�V����
#define TEXTURE_GAGE_POSITION002_X			(TEXTURE_GAGE_POSITION000_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION002_Y			(TEXTURE_GAGE_POSITION000_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION003_X			(TEXTURE_GAGE_POSITION001_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION003_Y			(TEXTURE_GAGE_POSITION001_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION004_X			(TEXTURE_GAGE_POSITION000_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION004_Y			(TEXTURE_GAGE_POSITION000_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION005_X			(TEXTURE_GAGE_POSITION001_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION005_Y			(TEXTURE_GAGE_POSITION001_Y)										// �|�W�V����



#define TEXTURE_GAGE_COLOR_DEFAULT000_R		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT000_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT000_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT000_A		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT001_R		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT001_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT001_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT001_A		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT002_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT002_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT002_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT002_A		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT003_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT003_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT003_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT003_A		(122)																// �e�N�X�`�����_�J���[�ω��O

#define TEXTURE_GAGE_COLOR_DEFAULT004_R		(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT004_G		(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT004_B		(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT004_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT005_R		(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT005_G		(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT005_B		(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT005_A		(255)																// �e�N�X�`�����_�J���[�ω��O


#define TEXTURE_GAGE_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_GAGE							(6)																	// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Gage : public ObjectManager
{
public:


	struct GageParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// �v���C���[�̈ړ���
		VERTEX_2D				vertexWk[NUM_VERTEX];					// ���_���i�[���[�N
		D3DXVECTOR2				TextureSize;
		D3DXVECTOR2				TextureSizeAdd;
		int						Count;
		int						Alfa;
		bool					Damege;
		bool					Use;									// true:�g�p  false:���g�p
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
	};
	GageParts GageObj[NUM_GAGE];
	void SetVertexGage(int CreateCount);
	void SetTextureGage(int i);
	HRESULT MakeVertexGage(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Gage();
	~Gage();
};


#endif
