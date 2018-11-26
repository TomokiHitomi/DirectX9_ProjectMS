//=============================================================================
//
// �v���C���[���� [titlelogo.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_TITLELOGO_000					"data/TEXTURE/logo001.png"											// ���S
#define TEXTURE_TITLELOGO_001					"data/TEXTURE/start001.png"											// ���S

#define TEXTURE_TITLELOGO_PIXEL000_X			(1167/2*SCREEN_SCALE)																// �s�N�Z���T�C�Y
#define TEXTURE_TITLELOGO_PIXEL000_Y			(1152/2*SCREEN_SCALE)																// �s�N�Z���T�C�Y
#define TEXTURE_TITLELOGO_PIXEL001_X			(500/2*SCREEN_SCALE)																// �s�N�Z���T�C�Y
#define TEXTURE_TITLELOGO_PIXEL001_Y			(146/2*SCREEN_SCALE)																// �s�N�Z���T�C�Y

#define TEXTURE_TITLELOGO_SIZE000_LATE_X		(1.0)																// �g��{��
#define TEXTURE_TITLELOGO_SIZE000_LATE_Y		(0.6)																// �g��{��
#define TEXTURE_TITLELOGO_SIZE001_LATE_X		(0.5)																// �g��{��
#define TEXTURE_TITLELOGO_SIZE001_LATE_Y		(0.5)																// �g��{��
#define TEXTURE_TITLELOGO_SIZE000_X				(TEXTURE_TITLELOGO_SIZE000_LATE_X*TEXTURE_TITLELOGO_PIXEL000_X)		// �T�C�Y
#define TEXTURE_TITLELOGO_SIZE000_Y				(TEXTURE_TITLELOGO_SIZE000_LATE_Y*TEXTURE_TITLELOGO_PIXEL000_Y)		// �T�C�Y
#define TEXTURE_TITLELOGO_SIZE001_X				(TEXTURE_TITLELOGO_SIZE001_LATE_X*TEXTURE_TITLELOGO_PIXEL001_X)		// �T�C�Y
#define TEXTURE_TITLELOGO_SIZE001_Y				(TEXTURE_TITLELOGO_SIZE001_LATE_Y*TEXTURE_TITLELOGO_PIXEL001_Y)		// �T�C�Y
#define TEXTURE_TITLELOGO_POSITION000_X			(SCREEN_WIDTH/2)													// �|�W�V����
#define TEXTURE_TITLELOGO_POSITION000_Y			(SCREEN_HEIGHT/2.8)												// �|�W�V����
#define TEXTURE_TITLELOGO_POSITION001_X			(SCREEN_WIDTH/2)													// �|�W�V����
#define TEXTURE_TITLELOGO_POSITION001_Y			(SCREEN_HEIGHT/1.20)												// �|�W�V����

#define TEXTURE_TITLELOGO_COLOR_DEFAULT_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLELOGO_COLOR_DEFAULT_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_TITLELOGO							(2)																	// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Titlelogo : public ObjectManager
{
public:


	struct TitlelogoParts
	{
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// �v���C���[�̈ړ���
		VERTEX_2D				vertexWk[NUM_VERTEX];					// ���_���i�[���[�N
		D3DXVECTOR2				TextureSize;
		int						Count;
		int						Alfa;
		bool					Flash;
		bool					Use;									// true:�g�p  false:���g�p
	};
	TitlelogoParts Title[NUM_TITLELOGO];
	void SetVertexTitlelogo(int CreateCount);
	void SetTextureTitlelogo(int i);
	HRESULT MakeVertexTitlelogo(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlelogo();
	~Titlelogo();
};


#endif
