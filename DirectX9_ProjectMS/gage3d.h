//=============================================================================
//
// プレイヤー処理 [gage3d.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _GAGE3D_H_
#define _GAGE3D_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_GAGE3D_000					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_001					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_002					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_003					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_004					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_005					"data/TEXTURE/gage000.png"											// gage3d hp
#define TEXTURE_GAGE3D_006					"data/TEXTURE/gage000.png"											// gage3d skill
#define TEXTURE_GAGE3D_007					"data/TEXTURE/gage000.png"											// gage3d skill
#define TEXTURE_GAGE3D_008					"data/TEXTURE/gage000.png"											// gage3d skill
#define TEXTURE_GAGE3D_009					"data/TEXTURE/gage000.png"											// gage3d skill
#define TEXTURE_GAGE3D_010					"data/NAME/ショウボウシ.png"										// name
#define TEXTURE_GAGE3D_011					"data/NAME/ドクター.png"											// name
#define TEXTURE_GAGE3D_012					"data/NAME/パティシエ.png"											// name
#define TEXTURE_GAGE3D_013					"data/NAME/アイドル.png"											// name
#define TEXTURE_GAGE3D_014					"data/NAME/ショウボウシ.png"										// name
#define TEXTURE_GAGE3D_015					"data/NAME/ドクター.png"											// name
#define TEXTURE_GAGE3D_016					"data/NAME/パティシエ.png"											// name
#define TEXTURE_GAGE3D_017					"data/NAME/アイドル.png"											// name


#define TEXTURE_GAGE3D_PIXEL000_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL000_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL001_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL001_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL002_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL002_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL003_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL003_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL004_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL004_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL005_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL005_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL006_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL006_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL007_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL007_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL008_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL008_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL009_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL009_Y				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL010_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL010_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL011_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL011_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL012_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL012_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL013_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL013_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL014_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL014_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL015_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL015_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL016_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL016_Y				(6000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL017_X				(1000)																// ピクセルサイズ
#define TEXTURE_GAGE3D_PIXEL017_Y				(6000)																// ピクセルサイズ


#define TEXTURE_GAGE3D_SIZE000_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE000_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE001_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE001_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE002_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE002_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE003_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE003_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE004_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE004_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE005_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE005_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE006_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE006_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE007_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE007_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE008_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE008_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE009_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE009_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE010_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE010_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE011_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE011_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE012_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE012_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE013_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE013_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE014_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE014_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE015_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE015_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE016_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE016_LATE_Y			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE017_LATE_X			(1.0)																// 拡大倍率
#define TEXTURE_GAGE3D_SIZE017_LATE_Y			(1.0)																// 拡大倍率

#define TEXTURE_GAGE3D_SCALE_X				(1.0)																// 斜めサイズ
#define TEXTURE_GAGE3D_SCALE_Y				(1.0)																// 斜めサイズ


#define TEXTURE_GAGE3D_SIZEADD_X				(TEXTURE_GAGE3D_SIZE000_LATE_X*SCREEN_WIDTH/128)						// 斜めサイズ
#define TEXTURE_GAGE3D_SIZEADD_Y				(TEXTURE_GAGE3D_SIZE000_LATE_Y*SCREEN_HEIGHT/512)						// 斜めサイズ

#define TEXTURE_GAGE3D_SIZE000_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE000_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE001_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE001_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE002_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE002_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE003_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE003_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE004_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE004_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE005_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE005_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE006_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE006_Y				(TEXTURE_GAGE3D_SIZEADD_Y/2)					// サイズ
#define TEXTURE_GAGE3D_SIZE007_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE007_Y				(TEXTURE_GAGE3D_SIZEADD_Y/2)					// サイズ
#define TEXTURE_GAGE3D_SIZE008_X				(TEXTURE_GAGE3D_SIZE008_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// サイズ
#define TEXTURE_GAGE3D_SIZE008_Y				(TEXTURE_GAGE3D_SIZEADD_Y/2)					// サイズ
#define TEXTURE_GAGE3D_SIZE009_X				(TEXTURE_GAGE3D_SIZE009_LATE_X*SCREEN_WIDTH/SCREEN_WIDTH/3)				// サイズ
#define TEXTURE_GAGE3D_SIZE009_Y				(TEXTURE_GAGE3D_SIZEADD_Y/2)					// サイズ
#define TEXTURE_GAGE3D_SIZE010_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE010_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE011_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE011_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE012_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE012_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE013_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE013_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE014_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE014_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE015_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE015_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE016_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE016_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ
#define TEXTURE_GAGE3D_SIZE017_X				(TEXTURE_GAGE3D_SIZEADD_X)					// サイズ
#define TEXTURE_GAGE3D_SIZE017_Y				(TEXTURE_GAGE3D_SIZEADD_Y)						// サイズ


#define TEXTURE_GAGE3D_OFFSET_POSITION000_X	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE3D_OFFSET_POSITION000_Y	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE3D_OFFSET_POSITION001_X	(0.0f)																// オフセットポジション
#define TEXTURE_GAGE3D_OFFSET_POSITION001_Y	(0.0f)											// オフセットポジション


#define TEXTURE_GAGE3D_POSITION000_X			(1.0f)		// ポジション
#define TEXTURE_GAGE3D_POSITION000_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION001_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION001_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION002_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION002_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION003_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION003_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION004_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION004_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION005_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION005_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION006_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION006_Y			(1.0f-TEXTURE_GAGE3D_SIZEADD_Y)	// ポジション
#define TEXTURE_GAGE3D_POSITION007_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION007_Y			(1.0f-TEXTURE_GAGE3D_SIZEADD_Y)	// ポジション
#define TEXTURE_GAGE3D_POSITION008_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION008_Y			(1.0f-TEXTURE_GAGE3D_SIZEADD_Y)	// ポジション
#define TEXTURE_GAGE3D_POSITION009_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION009_Y			(1.0f-TEXTURE_GAGE3D_SIZEADD_Y)	// ポジション
#define TEXTURE_GAGE3D_POSITION010_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION010_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION011_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION011_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION012_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION012_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION013_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION013_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION014_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION014_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION015_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION015_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION016_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION016_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION017_X			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION017_Y			(1.0f)	// ポジション
#define TEXTURE_GAGE3D_ANGLE_X					(0.5)	// ポジション
#define TEXTURE_GAGE3D_POSITION0UP_X			(20.0f)	// ポジション
#define TEXTURE_GAGE3D_POSITION0UP_Y			(25.0f)	// ポジション


#define TEXTURE_GAGE3D_COLOR_DEFAULT000_R		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT000_G		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT000_B		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT000_A		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT001_R		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT001_G		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT001_B		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT001_A		(0.5f)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE3D_COLOR_DEFAULT002_R		(1.0f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT002_G		(0.0f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT002_B		(0.0f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT002_A		(0.5f)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT003_R		(TEXTURE_GAGE3D_COLOR_DEFAULT002_R)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT003_G		(TEXTURE_GAGE3D_COLOR_DEFAULT002_G)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT003_B		(TEXTURE_GAGE3D_COLOR_DEFAULT002_B)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT003_A		(TEXTURE_GAGE3D_COLOR_DEFAULT002_A)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE3D_COLOR_DEFAULT004_R		(153.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT004_G		(204.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT004_B		(224.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT004_A		(255.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT005_R		(153.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT005_G		(204.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT005_B		(224.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT005_A		(255.0/255)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE3D_COLOR_DEFAULT006_R		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT006_G		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT006_B		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT006_A		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT007_R		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT007_G		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT007_B		(127.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT007_A		(127.5/255)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE3D_COLOR_DEFAULT008_R		(255.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT008_G		(229.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT008_B		(0)																	// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT008_A		(255.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT009_R		(255.0/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT009_G		(229.5/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT009_B		(0)																	// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT009_A		(255.0/255)																// テクスチャ頂点カラー変化前

#define TEXTURE_GAGE3D_COLOR_DEFAULT010_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT010_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT010_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT010_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT011_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT011_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT011_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT011_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT012_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT012_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT012_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT012_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT013_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT013_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT013_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT013_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT014_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT014_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT014_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT014_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT015_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT015_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT015_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT015_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT016_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT016_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT016_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT016_A		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT017_R		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT017_G		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT017_B		(255/255)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_DEFAULT017_A		(255/255)																// テクスチャ頂点カラー変化前


#define TEXTURE_GAGE3D_COLOR_CHANGE_R			(153)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_CHANGE_G			(204)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_CHANGE_B			(224)																// テクスチャ頂点カラー変化前
#define TEXTURE_GAGE3D_COLOR_CHANGE_A			(255)																// テクスチャ頂点カラー変化前
#define NUM_GAGE3D							(18)																	// テクスチャの数
#define TEXTURE_GAGE3D_MAX_HP						(1000)
#define OFFSET_DAMEGE_000							(2)
#define DAMEGE_000							(10)
#define SKILL_000							(1)
//=============================================================================
//
//SELECT構造体
//
//=============================================================================
class Gage3d : public ObjectManager
{
public:


	struct Gage3dParts
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
		bool					Damege;
		bool					Use;									// true:使用  false:未使用
		LPDIRECT3DTEXTURE9		pD3DTexture;							// テクスチャへのポリゴン (*33)
		float					NowHp;
		float					NowSkill;
		D3DXMATRIX					mtxWorld;
		D3DXMATRIX				mtxView;
		D3DXVECTOR3					pos;										// 地面の位置
		D3DXVECTOR3					rot;										// 地面の向き(回転)
		D3DXVECTOR3					scl;										// 地面の大きさ(スケール)
		LPD3DXBUFFER				pD3DXBuffMat;								// マテリアル情報へのポインタ
		DWORD						nNumMat;									// マテリアル情報の数
		LPD3DXMESH					pD3DXMesh;									// メッシュ情報へのポインタ
		LPDIRECT3DVERTEXBUFFER9		pD3DVtxBuff;	// 頂点バッファへのポインタ
		VERTEX_3D					*pVtx;

	};
	Gage3dParts Gage3dObj[NUM_GAGE3D];
	void SetVertexGage3d(int CreateCount);
	void SetTextureGage3d(int i);
	HRESULT MakeVertexGage3d(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetGage3d(D3DXVECTOR3 Pos);
	void DamegeReduce(float Damege, int player);
	void DamegeAdd(float Damege, int player);
	void SkillReduce(float Damege, int player);
	void SkillAdd(float Damege, int player);
	Gage3d();
	~Gage3d();
};


#endif
