//=============================================================================
//
// �^�C�g������ [title.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TITLE_SELECT00				"data/TEXTURE/logo000.png"											// ���S
#define TEXTURE_TITLE_SIZE000_LATE			(2.0)																// �g��{��
#define TEXTURE_TITLE_SIZE000_X				(TEXTURE_TITLE_SIZE000_LATE*SCREEN_WIDTH/SCREEN_WIDTH)					// �T�C�Y
#define TEXTURE_TITLE_SIZE000_Y				(TEXTURE_TITLE_SIZE000_LATE*SCREEN_HEIGHT/SCREEN_HEIGHT)				// �T�C�Y
#define tEXTURE_TITLE_POSITION000X			(SCREEN_WIDTH/2)
#define tEXTURE_TITLE_POSITION000_Y			(SCREEN_HEIGHT/2)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TitleScene :public BaseScene
{   // :public  BaseScene
public:
	TitleScene(void);
	~TitleScene(void);
	void Update(void);
	void Draw(void);
private:
	void DemoRestart(void);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif