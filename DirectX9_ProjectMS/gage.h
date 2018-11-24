//=============================================================================
//
// プレイヤー処理 [gage.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_GAGE_000					"data/TEXTURE/white_1x1.png"											// gage hp半透明gray
#define TEXTURE_GAGE_001					"data/TEXTURE/white_1x1.png"											// gage hp半透明gray
#define TEXTURE_GAGE_002					"data/TEXTURE/white_1x1.png"											// gage hp赤
#define TEXTURE_GAGE_003					"data/TEXTURE/white_1x1.png"											// gage hp赤
#define TEXTURE_GAGE_004					"data/TEXTURE/white_1x1.png"											// gage hp青
#define TEXTURE_GAGE_005					"data/TEXTURE/white_1x1.png"											// gage hp青
#define TEXTURE_GAGE_006					"data/TEXTURE/white_1x1.png"											// gage skill半透明gray
#define TEXTURE_GAGE_007					"data/TEXTURE/white_1x1.png"											// gage skill半透明gray
#define TEXTURE_GAGE_008					"data/TEXTURE/white_1x1.png"											// gage skill黄
#define TEXTURE_GAGE_009					"data/TEXTURE/white_1x1.png"											// gage skill黄
#define TEXTURE_GAGE_010					"data/NAME/ショウボウシ.png"										// name
#define TEXTURE_GAGE_011					"data/NAME/ドクター.png"											// name
#define TEXTURE_GAGE_012					"data/NAME/パティシエ.png"											// name
#define TEXTURE_GAGE_013					"data/NAME/アイドル.png"											// name
#define TEXTURE_GAGE_014					"data/NAME/ショウボウシ.png"										// name
#define TEXTURE_GAGE_015					"data/NAME/ドクター.png"											// name
#define TEXTURE_GAGE_016					"data/NAME/パティシエ.png"											// name
#define TEXTURE_GAGE_017					"data/NAME/アイドル.png"											// name


#define TEXTURE_GAGE_PIXEL000_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL000_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL001_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL001_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL002_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL002_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL003_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL003_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL004_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL004_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL005_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL005_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL006_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL006_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL007_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL007_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL008_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL008_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL009_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL009_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL010_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL010_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL011_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL011_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL012_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL012_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL013_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL013_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL014_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL014_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL015_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL015_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL016_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL016_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL017_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE_PIXEL017_Y				(6000)																// ピクセルサイズ


#define TEXTURE_GAGE_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE000_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE001_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE001_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE002_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE002_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE003_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE003_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE004_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE004_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE005_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE005_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE006_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE006_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE007_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE007_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE008_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE008_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE009_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE009_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE010_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE010_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE011_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE011_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE012_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE012_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE013_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE013_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE014_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE014_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE015_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE015_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE016_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE016_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE017_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE_SIZE017_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_GAGE_SCALE_X				(1.0)																// 斜めサイズ
#define TEXTURE_GAGE_SCALE_Y				(1.0)																// 斜めサイズ

#define TEXTURE_GAGE_SIZE_X					(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)

#define TEXTURE_GAGE_SIZEADD_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/4)						// 斜めサイズ
#define TEXTURE_GAGE_SIZEADD_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// 斜めサイズ

#define TEXTURE_GAGE_SIZE000_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE000_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE001_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE001_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE002_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE002_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE003_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE003_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE004_X				(TEXTURE_GAGE_SIZE004_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE004_Y				(TEXTURE_GAGE_SIZE004_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE005_X				(TEXTURE_GAGE_SIZE005_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE005_Y				(TEXTURE_GAGE_SIZE005_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE006_X				(TEXTURE_GAGE_SIZE006_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE006_Y				(TEXTURE_GAGE_SIZE006_LATE_Y*SCREEN_HEIGHT/16/2)					// サイズ
#define TEXTURE_GAGE_SIZE007_X				(TEXTURE_GAGE_SIZE007_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE007_Y				(TEXTURE_GAGE_SIZE007_LATE_Y*SCREEN_HEIGHT/16/2)					// サイズ
#define TEXTURE_GAGE_SIZE008_X				(TEXTURE_GAGE_SIZE008_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// サイズ
#define TEXTURE_GAGE_SIZE008_Y				(TEXTURE_GAGE_SIZE008_LATE_Y*SCREEN_HEIGHT/16/2)					// サイズ
#define TEXTURE_GAGE_SIZE009_X				(TEXTURE_GAGE_SIZE009_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// サイズ
#define TEXTURE_GAGE_SIZE009_Y				(TEXTURE_GAGE_SIZE009_LATE_Y*SCREEN_HEIGHT/16/2)					// サイズ
#define TEXTURE_GAGE_SIZE010_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE010_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE011_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE011_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE012_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE012_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE013_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE013_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE014_X				(TEXTURE_GAGE_SIZE000_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE014_Y				(TEXTURE_GAGE_SIZE000_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE015_X				(TEXTURE_GAGE_SIZE001_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE015_Y				(TEXTURE_GAGE_SIZE001_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE016_X				(TEXTURE_GAGE_SIZE002_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE016_Y				(TEXTURE_GAGE_SIZE002_LATE_Y*SCREEN_HEIGHT/16)						// サイズ
#define TEXTURE_GAGE_SIZE017_X				(TEXTURE_GAGE_SIZE003_LATE_X*SCREEN_WIDTH/6)						// サイズ
#define TEXTURE_GAGE_SIZE017_Y				(TEXTURE_GAGE_SIZE003_LATE_Y*SCREEN_HEIGHT/16)						// サイズ


#define TEXTURE_GAGE_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE_OFFSET_POSITION001_X	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE_OFFSET_POSITION001_Y	(TEXTURE_GAGE_SIZEADD_Y)											// オフセットポジション


#define TEXTURE_GAGE_POSITION000_X			(TEXTURE_GAGE_OFFSET_POSITION000_X+SCREEN_WIDTH/2-TEXTURE_GAGE_SIZE_X)					// ポジション
#define TEXTURE_GAGE_POSITION000_Y			(TEXTURE_GAGE_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// ポジション
#define TEXTURE_GAGE_POSITION001_X			(TEXTURE_GAGE_OFFSET_POSITION000_X+SCREEN_WIDTH-TEXTURE_GAGE_SIZE_X)	// ポジション
#define TEXTURE_GAGE_POSITION001_Y			(TEXTURE_GAGE_OFFSET_POSITION000_Y+SCREEN_HEIGHT/2+SCREEN_HEIGHT/4)	// ポジション
#define TEXTURE_GAGE_POSITION002_X			(TEXTURE_GAGE_POSITION000_X)										// ポジション
#define TEXTURE_GAGE_POSITION002_Y			(TEXTURE_GAGE_POSITION000_Y)										// ポジション
#define TEXTURE_GAGE_POSITION003_X			(TEXTURE_GAGE_POSITION001_X)										// ポジション
#define TEXTURE_GAGE_POSITION003_Y			(TEXTURE_GAGE_POSITION001_Y)										// ポジション
#define TEXTURE_GAGE_POSITION004_X			(TEXTURE_GAGE_POSITION000_X)										// ポジション
#define TEXTURE_GAGE_POSITION004_Y			(TEXTURE_GAGE_POSITION000_Y)										// ポジション
#define TEXTURE_GAGE_POSITION005_X			(TEXTURE_GAGE_POSITION001_X)										// ポジション
#define TEXTURE_GAGE_POSITION005_Y			(TEXTURE_GAGE_POSITION001_Y)										// ポジション
#define TEXTURE_GAGE_POSITION006_X			(TEXTURE_GAGE_POSITION000_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// ポジション
#define TEXTURE_GAGE_POSITION006_Y			(TEXTURE_GAGE_POSITION000_Y+TEXTURE_GAGE_OFFSET_POSITION001_Y)		// ポジション
#define TEXTURE_GAGE_POSITION007_X			(TEXTURE_GAGE_POSITION001_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// ポジション
#define TEXTURE_GAGE_POSITION007_Y			(TEXTURE_GAGE_POSITION001_Y+TEXTURE_GAGE_OFFSET_POSITION001_Y)		// ポジション
#define TEXTURE_GAGE_POSITION008_X			(TEXTURE_GAGE_POSITION006_X)										// ポジション
#define TEXTURE_GAGE_POSITION008_Y			(TEXTURE_GAGE_POSITION006_Y)										// ポジション
#define TEXTURE_GAGE_POSITION009_X			(TEXTURE_GAGE_POSITION007_X)										// ポジション
#define TEXTURE_GAGE_POSITION009_Y			(TEXTURE_GAGE_POSITION007_Y)										// ポジション
#define TEXTURE_GAGE_POSITION010_X			(TEXTURE_GAGE_POSITION000_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// ポジション
#define TEXTURE_GAGE_POSITION010_Y			(TEXTURE_GAGE_POSITION000_Y-TEXTURE_GAGE_OFFSET_POSITION001_Y)		// ポジション
#define TEXTURE_GAGE_POSITION011_X			(TEXTURE_GAGE_POSITION010_X)										// ポジション
#define TEXTURE_GAGE_POSITION011_Y			(TEXTURE_GAGE_POSITION010_Y)										// ポジション
#define TEXTURE_GAGE_POSITION012_X			(TEXTURE_GAGE_POSITION010_X)										// ポジション
#define TEXTURE_GAGE_POSITION012_Y			(TEXTURE_GAGE_POSITION010_Y)										// ポジション
#define TEXTURE_GAGE_POSITION013_X			(TEXTURE_GAGE_POSITION010_X)										// ポジション
#define TEXTURE_GAGE_POSITION013_Y			(TEXTURE_GAGE_POSITION010_Y)										// ポジション
#define TEXTURE_GAGE_POSITION014_X			(TEXTURE_GAGE_POSITION001_X+TEXTURE_GAGE_OFFSET_POSITION001_X)		// ポジション
#define TEXTURE_GAGE_POSITION014_Y			(TEXTURE_GAGE_POSITION001_Y-TEXTURE_GAGE_OFFSET_POSITION001_Y)		// ポジション
#define TEXTURE_GAGE_POSITION015_X			(TEXTURE_GAGE_POSITION014_X)										// ポジション
#define TEXTURE_GAGE_POSITION015_Y			(TEXTURE_GAGE_POSITION014_Y)										// ポジション
#define TEXTURE_GAGE_POSITION016_X			(TEXTURE_GAGE_POSITION014_X)										// ポジション
#define TEXTURE_GAGE_POSITION016_Y			(TEXTURE_GAGE_POSITION014_Y)										// ポジション
#define TEXTURE_GAGE_POSITION017_X			(TEXTURE_GAGE_POSITION014_X)										// ポジション
#define TEXTURE_GAGE_POSITION017_Y			(TEXTURE_GAGE_POSITION014_Y)										// ポジション
#define TEXTURE_GAGE_ANGLE_X				(-0.5)																// ポジション



#define TEXTURE_GAGE_COLOR_DEFAULT000_R		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT000_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT000_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT000_A		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT001_R		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT001_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT001_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT001_A		(122)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE_COLOR_DEFAULT002_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT002_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT002_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT002_A		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT003_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT003_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT003_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT003_A		(122)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE_COLOR_DEFAULT004_R		(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT004_G		(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT004_B		(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT004_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT005_R		(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT005_G		(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT005_B		(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT005_A		(255)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE_COLOR_DEFAULT006_R		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT006_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT006_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT006_A		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT007_R		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT007_G		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT007_B		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT007_A		(122)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT008_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT008_G		(241)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT008_B		(0)																	// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT008_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT009_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT009_G		(241)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT009_B		(0)																	// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT009_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT010_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT010_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT010_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT010_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT011_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT011_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT011_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT011_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT012_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT012_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT012_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT012_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT013_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT013_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT013_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT013_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT014_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT014_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT014_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT014_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT015_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT015_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT015_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT015_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT016_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT016_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT016_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT016_A		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT017_R		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT017_G		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT017_B		(255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_DEFAULT017_A		(255)																// テクスチャ頂点カラー変化前


#define TEXTURE_GAGE_COLOR_CHANGE_R			(157)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define NUM_GAGE							(18)																	// テクスチャの数

//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Gage : public ObjectManager
{
public:


	struct GageParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// プレイヤーの移動量
		VERTEX_2D				vertexWk[NUM_VERTEX];					// 頂点情報格納ワーク
		D3DXVECTOR2				TextureSize;
		D3DXVECTOR2				TextureSizeAdd;
		D3DXVECTOR2				Scale;
		float					Angle;
		int						Count;
		int						Alfa;
		float					NowHp;
		float					NowSkill;
		bool					Damege;
		bool					Use;									// true:使用  false:未使用
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)

		//D3DXMATRIX					mtxWorld;
		//D3DXVECTOR3					pos;										// 地面の位置
		//D3DXVECTOR3					rot;										// 地面の向き(回転)
		//D3DXVECTOR3					scl;										// 地面の大きさ(スケール)
		//LPD3DXBUFFER				pD3DXBuffMat;								// マテリアル情報へのポインタ
		//DWORD						nNumMat;									// マテリアル情報の数
		//LPD3DXMESH					pD3DXMesh;									// メッシュ情報へのポインタ
		//LPDIRECT3DVERTEXBUFFER9		pD3DVtxBuff;	// 頂点バッファへのポインタ


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
