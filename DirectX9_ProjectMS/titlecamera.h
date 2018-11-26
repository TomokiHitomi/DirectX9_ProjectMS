//=============================================================================
//
// �v���C���[���� [ko.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _TITLECAMERA_H_
#define _TITLECAMERA_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================



#define TEXTURE_TITLECAMERA_SCOND						(3)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLECAMERA_SCOND_COUNT				(2)
#define TEXTURE_TITLECAMERA_SCOND_COUNT_COLOR			(255.0f /TEXTURE_TITLECAMERA_SCOND_COUNT)
#define TEXTURE_TITLECAMERA_SCOND_TIME				(FRAME*TEXTURE_TITLECAMERA_SCOND)									//300
#define TEXTURE_TITLECAMERA_SCOND_COLOR				(TEXTURE_TITLECAMERA_SCOND_COUNT_COLOR/TEXTURE_TITLECAMERA_SCOND_TIME)								//90
#define TITLECAMERA_LENGTH							(125.0f)
#define NUM_TITLECAMERA								(1)																// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Titlecamera : public ObjectManager
{
public:


	struct TitlecameraParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// �v���C���[�̈ړ���
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		float					Color;
		bool					Use;									// true:�g�p  false:���g�p
		bool					Nowselect;
	};
	TitlecameraParts TitlecameraObj[NUM_TITLECAMERA];
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlecamera();
	~Titlecamera();
};


#endif
