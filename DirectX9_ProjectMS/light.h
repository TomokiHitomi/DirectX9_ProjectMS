//=============================================================================
//
// ���C�g���� [light.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	LIGHT_MAX				(3)						// ���C�g�̐�

#define LIGHT_DIFFUSE_0			(1.0f)
#define LIGHT_DIFFUSE_1			(0.5f)
#define LIGHT_DIFFUSE_2			(0.5f)
#define LIGHT_AMBIENT			(0.6f)


#define LIGHT_SUB_DIFFUSE		(0.3f)
#define LIGHT_SUB_XZ			(0.8)
#define LIGHT_SUB_Y				(1.0f)

enum
{
	LIGHT_MAIN,
	LIGHT_SUB1,
	LIGHT_SUB2
};

class Light
{
public:
	typedef struct _LIGHTVALUE
	{
		D3DCOLORVALUE   Diffuse;	// �g�U��
		D3DCOLORVALUE   Ambient;	// ����
		D3DCOLORVALUE   Specular;	// ���ˌ�
		D3DVECTOR       Position;	// ���W
		D3DVECTOR       Direction;	// ���s����
	}LIGHTVALUE;
	typedef enum _LIGHTTYPE
	{
		POINT,
		SPOT,
		DIRECTIONAL
	}LIGHTTYPE;

	LIGHTTYPE type;
	LIGHTVALUE value;

	// �R���X�g���N�^
	Light()
	{
		type = DIRECTIONAL;
		ZeroMemory(&value, sizeof(value));
	}
};

class LightManager
{
public:
	enum LightArray
	{
		Main,
		Max
	};
	static Light cLight[Max];

	static HRESULT Init();
	static Light *GetLightAdr(LightArray eLight) { return &cLight[eLight]; }
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLight(void);
void SetLight(int nLight, bool bFlag);
D3DLIGHT9 GetLight(int nLight);

#endif
