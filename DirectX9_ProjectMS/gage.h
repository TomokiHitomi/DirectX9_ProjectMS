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
#define TEXTURE_GAGE_000					"data/TEXTURE/white_1x1.png"											// gage hp������gray
#define TEXTURE_GAGE_001					"data/TEXTURE/white_1x1.png"											// gage hp������gray
#define TEXTURE_GAGE_002					"data/TEXTURE/white_1x1.png"											// gage hp��
#define TEXTURE_GAGE_003					"data/TEXTURE/white_1x1.png"											// gage hp��
#define TEXTURE_GAGE_004					"data/TEXTURE/white_1x1.png"											// gage hp��
#define TEXTURE_GAGE_005					"data/TEXTURE/white_1x1.png"											// gage hp��
#define TEXTURE_GAGE_006					"data/TEXTURE/white_1x1.png"											// gage skill������gray
#define TEXTURE_GAGE_007					"data/TEXTURE/white_1x1.png"											// gage skill������gray
#define TEXTURE_GAGE_008					"data/TEXTURE/white_1x1.png"											// gage skill��
#define TEXTURE_GAGE_009					"data/TEXTURE/white_1x1.png"											// gage skill��
#define TEXTURE_GAGE_010					"data/NAME/�V���E�{�E�V.png"										// name
#define TEXTURE_GAGE_011					"data/NAME/�h�N�^�[.png"											// name
#define TEXTURE_GAGE_012					"data/NAME/�p�e�B�V�G.png"											// name
#define TEXTURE_GAGE_013					"data/NAME/�A�C�h��.png"											// name
#define TEXTURE_GAGE_014					"data/NAME/�V���E�{�E�V.png"										// name
#define TEXTURE_GAGE_015					"data/NAME/�h�N�^�[.png"											// name
#define TEXTURE_GAGE_016					"data/NAME/�p�e�B�V�G.png"											// name
#define TEXTURE_GAGE_017					"data/NAME/�A�C�h��.png"											// name


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
#define TEXTURE_GAGE_PIXEL006_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL006_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL007_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL007_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL008_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL008_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL009_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL009_Y				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL010_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL010_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL011_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL011_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL012_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL012_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL013_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL013_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL014_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL014_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL015_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL015_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL016_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL016_Y				(6000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL017_X				(1000)																// �s�N�Z���T�C�Y
#define TEXTURE_GAGE_PIXEL017_Y				(6000)																// �s�N�Z���T�C�Y


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
#define TEXTURE_GAGE_SIZE006_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE006_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE007_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE007_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE008_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE008_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE009_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE009_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE010_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE010_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE011_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE011_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE012_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE012_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE013_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE013_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE014_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE014_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE015_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE015_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE016_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE016_LATE_Y			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE017_LATE_X			(1.0)																// �g��{��
#define TEXTURE_GAGE_SIZE017_LATE_Y			(1.0)																// �g��{��

#define TEXTURE_GAGE_SCALE_X				(1.0)																// �΂߃T�C�Y
#define TEXTURE_GAGE_SCALE_Y				(1.0)																// �΂߃T�C�Y

#define TEXTURE_GAGE_SIZE_X					(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)

#define TEXTURE_GAGE_SIZEADD_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/4)						// �΂߃T�C�Y
#define TEXTURE_GAGE_SIZEADD_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �΂߃T�C�Y

#define TEXTURE_GAGE_SIZE000_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE000_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE001_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE001_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE002_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE002_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE003_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE003_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE004_X				(TEXTURE_GAGE_SIZE004_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE004_Y				(TEXTURE_GAGE_SIZE004_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE005_X				(TEXTURE_GAGE_SIZE005_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE005_Y				(TEXTURE_GAGE_SIZE005_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE006_X				(TEXTURE_GAGE_SIZE006_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE006_Y				(TEXTURE_GAGE_SIZE006_LATE_Y*SCREEN_HEIGHT/16/2)					// �T�C�Y
#define TEXTURE_GAGE_SIZE007_X				(TEXTURE_GAGE_SIZE007_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE007_Y				(TEXTURE_GAGE_SIZE007_LATE_Y*SCREEN_HEIGHT/16/2)					// �T�C�Y
#define TEXTURE_GAGE_SIZE008_X				(TEXTURE_GAGE_SIZE008_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// �T�C�Y
#define TEXTURE_GAGE_SIZE008_Y				(TEXTURE_GAGE_SIZE008_LATE_Y*SCREEN_HEIGHT/16/2)					// �T�C�Y
#define TEXTURE_GAGE_SIZE009_X				(TEXTURE_GAGE_SIZE009_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// �T�C�Y
#define TEXTURE_GAGE_SIZE009_Y				(TEXTURE_GAGE_SIZE009_LATE_Y*SCREEN_HEIGHT/16/2)					// �T�C�Y
#define TEXTURE_GAGE_SIZE010_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE010_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE011_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE011_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE012_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE012_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE013_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE013_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE014_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE014_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE015_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE015_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE016_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE016_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y
#define TEXTURE_GAGE_SIZE017_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// �T�C�Y
#define TEXTURE_GAGE_SIZE017_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// �T�C�Y


#define TEXTURE_GAGE_OFFSET_POSITION000_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION000_Y	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION001_X	(0.0f)																// �I�t�Z�b�g�|�W�V����
#define TEXTURE_GAGE_OFFSET_POSITION001_Y	(TEXTURE_GAGE_SIZEADD_Y)											// �I�t�Z�b�g�|�W�V����


#define TEXTURE_GAGE_POSITION000_X			(TEXTURE_GAGE_OFFSET_POSITION000_X+SCREEN_WIDTH/2-TEXTURE_GAGE_SIZE_X)					// �|�W�V����
#define TEXTURE_GAGE_POSITION000_Y			(TEXTURE_GAGE_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// �|�W�V����
#define TEXTURE_GAGE_POSITION001_X			(TEXTURE_GAGE_OFFSET_POSITION000_X+SCREEN_WIDTH-TEXTURE_GAGE_SIZE_X)	// �|�W�V����
#define TEXTURE_GAGE_POSITION001_Y			(TEXTURE_GAGE_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// �|�W�V����
#define TEXTURE_GAGE_POSITION002_X			(TEXTURE_GAGE_POSITION000_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION002_Y			(TEXTURE_GAGE_POSITION000_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION003_X			(TEXTURE_GAGE_POSITION001_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION003_Y			(TEXTURE_GAGE_POSITION001_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION004_X			(TEXTURE_GAGE_POSITION000_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION004_Y			(TEXTURE_GAGE_POSITION000_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION005_X			(TEXTURE_GAGE_POSITION001_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION005_Y			(TEXTURE_GAGE_POSITION001_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION006_X			(TEXTURE_GAGE_POSITION000_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// �|�W�V����
#define TEXTURE_GAGE_POSITION006_Y			(TEXTURE_GAGE_POSITION000_Y+TEXTURE_GAGE_OFFSET_POSITION001_Y)		// �|�W�V����
#define TEXTURE_GAGE_POSITION007_X			(TEXTURE_GAGE_POSITION001_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// �|�W�V����
#define TEXTURE_GAGE_POSITION007_Y			(TEXTURE_GAGE_POSITION001_Y+TEXTURE_GAGE_OFFSET_POSITION001_Y)		// �|�W�V����
#define TEXTURE_GAGE_POSITION008_X			(TEXTURE_GAGE_POSITION006_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION008_Y			(TEXTURE_GAGE_POSITION006_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION009_X			(TEXTURE_GAGE_POSITION007_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION009_Y			(TEXTURE_GAGE_POSITION007_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION010_X			(TEXTURE_GAGE_POSITION000_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// �|�W�V����
#define TEXTURE_GAGE_POSITION010_Y			(TEXTURE_GAGE_POSITION000_Y-TEXTURE_GAGE_OFFSET_POSITION001_Y)		// �|�W�V����
#define TEXTURE_GAGE_POSITION011_X			(TEXTURE_GAGE_POSITION010_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION011_Y			(TEXTURE_GAGE_POSITION010_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION012_X			(TEXTURE_GAGE_POSITION010_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION012_Y			(TEXTURE_GAGE_POSITION010_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION013_X			(TEXTURE_GAGE_POSITION010_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION013_Y			(TEXTURE_GAGE_POSITION010_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION014_X			(TEXTURE_GAGE_POSITION001_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// �|�W�V����
#define TEXTURE_GAGE_POSITION014_Y			(TEXTURE_GAGE_POSITION001_Y-TEXTURE_GAGE_OFFSET_POSITION001_Y)		// �|�W�V����
#define TEXTURE_GAGE_POSITION015_X			(TEXTURE_GAGE_POSITION014_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION015_Y			(TEXTURE_GAGE_POSITION014_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION016_X			(TEXTURE_GAGE_POSITION014_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION016_Y			(TEXTURE_GAGE_POSITION014_Y)										// �|�W�V����
#define TEXTURE_GAGE_POSITION017_X			(TEXTURE_GAGE_POSITION014_X)										// �|�W�V����
#define TEXTURE_GAGE_POSITION017_Y			(TEXTURE_GAGE_POSITION014_Y)										// �|�W�V����
#define TEXTURE_GAGE_ANGLE_X				(-0.5)																// �|�W�V����



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

#define TEXTURE_GAGE_COLOR_DEFAULT006_R		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT006_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT006_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT006_A		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT007_R		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT007_G		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT007_B		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT007_A		(122)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT008_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT008_G		(241)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT008_B		(0)																	// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT008_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT009_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT009_G		(241)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT009_B		(0)																	// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT009_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT010_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT010_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT010_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT010_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT011_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT011_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT011_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT011_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT012_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT012_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT012_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT012_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT013_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT013_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT013_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT013_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT014_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT014_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT014_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT014_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT015_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT015_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT015_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT015_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT016_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT016_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT016_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT016_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT017_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT017_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT017_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_DEFAULT017_A		(255)																// �e�N�X�`�����_�J���[�ω��O


#define TEXTURE_GAGE_COLOR_CHANGE_R			(157)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_G			(204)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_B			(224)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_GAGE_COLOR_CHANGE_A			(255)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_GAGE							(18)																	// �e�N�X�`���̐�

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
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		float					NowHp;
		float					NowSkill;
		bool					Damege;
		bool					Use;									// true:�g�p  false:���g�p
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)

		//D3DXMATRIX					mtxWorld;
		//D3DXVECTOR3					pos;										// �n�ʂ̈ʒu
		//D3DXVECTOR3					rot;										// �n�ʂ̌���(��])
		//D3DXVECTOR3					scl;										// �n�ʂ̑傫��(�X�P�[��)
		//LPD3DXBUFFER				pD3DXBuffMat;								// �}�e���A�����ւ̃|�C���^
		//DWORD						nNumMat;									// �}�e���A�����̐�
		//LPD3DXMESH					pD3DXMesh;									// ���b�V�����ւ̃|�C���^
		//LPDIRECT3DVERTEXBUFFER9		pD3DVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^


	};
	GageParts GageObj[NUM_GAGE];
	void SetVertexGage(int CreateCount);
	void SetTextureGage(int i);
	HRESULT MakeVertexGage(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DamegeReduce(float Dmege,int player);
	void DamegeAdd(float Dmege, int player);
	void SkillReduce(float Dmege, int player);
	void SkillAdd(float Dmege, int player);
	Gage();
	~Gage();
};


#endif
