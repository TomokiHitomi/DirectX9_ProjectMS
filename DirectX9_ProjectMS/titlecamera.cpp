//=============================================================================
//
// プレイヤー処理 [ko.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titlecamera.h"
#include "camera.h"
#include "character.h"
#include "calculate.h"
#include <math.h>
// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Titlecamera::Titlecamera()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::TITLECAMERA, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Titlecamera::~Titlecamera()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Titlecamera::Init()
{
	TitlecameraObj[0].Pos = D3DXVECTOR3(0.0, 30.0, 90.0);
	TitlecameraObj[0].Angle = 0.0f;

	// カメラをAtをモデルに設定
	CameraManager::pCamera[CameraManager::SINGLE]->SetAt(ZERO_D3DXVECTOR3);

	// カメラEyeをモデル後方にセット
	CameraManager::pCamera[CameraManager::SINGLE]->SetEye(ZERO_D3DXVECTOR3 + TitlecameraObj[0].Pos);

	TitlecameraObj[0].Use = true;
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Titlecamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Titlecamera::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG

#endif
	TitlecameraObj[0].Angle += TITLECAMERA_ROT_SPEED;
	TitlecameraObj[0].Pos.x = sinf(TitlecameraObj[0].Angle)*TITLECAMERA_LENGTH;
	TitlecameraObj[0].Pos.z = cosf(TitlecameraObj[0].Angle)*TITLECAMERA_LENGTH;
	// カメラをAtをモデルに設定
	CameraManager::pCamera[CameraManager::SINGLE]->SetAt(ZERO_D3DXVECTOR3);
	//Camera::SetAt(m_vTag, m_nNum);

	// カメラEyeをモデル後方にセット
	CameraManager::pCamera[CameraManager::SINGLE]->SetEye(ZERO_D3DXVECTOR3 + TitlecameraObj[0].Pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void Titlecamera::Draw(void)
{

}
