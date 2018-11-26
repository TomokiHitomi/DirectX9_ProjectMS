//=============================================================================
//
// �v���C���[���� [gary.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _GRAYKO_H_
#define _GRAYKO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_GRAYKO_000					"data/TEXTURE/white_1x1.png"												// gage hp




#define TEXTURE_GRAYKO_PIXEL000_X				(1)																// �s�N�Z���T�C�Y
#define TEXTURE_GRAYKO_PIXEL000_Y				(1)																// �s�N�Z���T�C�Y

#define TEXTURE_GRAYKO_SIZE000_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GRAYKO_SIZE000_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_GRAYKO_SCALE_X				(1.0)																// �΂߃T�C�Y
#define TEXTURE_GRAYKO_SCALE_Y				(1.0)																// �΂߃T�C�Y


#define TEXTURE_GRAYKO_SIZE000_X				(TEXTURE_GRAYKO_SIZE000_LATE_X*SCREEN_WIDTH)						// �T�C�Y
#define TEXTURE_GRAYKO_SIZE000_Y				(TEXTURE_GRAYKO_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// �T�C�Y


#define TEXTURE_GRAYKO_SIZE001_X				(TEXTURE_GRAYKO_SIZE000_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GRAYKO_SIZE001_Y				(TEXTURE_GRAYKO_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// �T�C�Y
#define TEXTURE_GRAYKO_SIZE002_X				(TEXTURE_GRAYKO_SIZE000_LATE_X*SCREEN_WIDTH/4)						// �T�C�Y
#define TEXTURE_GRAYKO_SIZE002_Y				(TEXTURE_GRAYKO_SIZE000_LATE_Y*SCREEN_HEIGHT/2)						// �T�C�Y

#define TEXTURE_GRAYKO_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GRAYKO_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����


#define TEXTURE_GRAYKO_POSITION000_X			(TEXTURE_GRAYKO_OFFSET_POSITION000_X+SCREEN_WIDTH/2)					// �|�W�V����
#define TEXTURE_GRAYKO_POSITION000_Y			(TEXTURE_GRAYKO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_GRAYKO_POSITION001_X			(TEXTURE_GRAYKO_OFFSET_POSITION000_X+SCREEN_WIDTH/4)					// �|�W�V����
#define TEXTURE_GRAYKO_POSITION001_Y			(TEXTURE_GRAYKO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_GRAYKO_POSITION002_X			(TEXTURE_GRAYKO_OFFSET_POSITION000_X+SCREEN_WIDTH/2+SCREEN_WIDTH/4)					// �|�W�V����
#define TEXTURE_GRAYKO_POSITION002_Y			(TEXTURE_GRAYKO_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2)	// �|�W�V����
#define TEXTURE_GRAYKO_ANGLE_X				(0.0)																// �|�W�V����



#define TEXTURE_GRAYKO_COLOR_DEFAULT000_R		(0)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_DEFAULT000_G		(0)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_DEFAULT000_B		(0)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_DEFAULT000_A		(127)																// �e�N�X�`�����_�J���[�ω��O

#define TEXTURE_GRAYKO_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GRAYKO_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_GRAYKO							(2)																// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Grayko : public ObjectManager
{
public:


	struct GraykoParts
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
		bool					Use;									// true:�g�p  false:���g�p
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
		bool					Nowselect;
	};
	GraykoParts GraykoObj[NUM_GRAYKO];
	void SetVertexGrayko(int CreateCount);
	void SetTextureGrayko(int i);
	HRESULT MakeVertexGrayko(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Grayko();
	~Grayko();
};


#endif
