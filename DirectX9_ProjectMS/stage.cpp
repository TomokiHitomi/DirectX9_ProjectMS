//=============================================================================
//
// ステージ処理 [stage.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "stage.h"
#include "calculate.h"

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
// コンストラクタ（初期化処理）
//=============================================================================
StageManager::StageManager(void)
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::STAGE, Priority::Middle, Priority::Lowest);

	m_pStage = NULL;

	SetStage<StageChinese>();
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
StageManager::~StageManager(void)
{
	ReleaseStage();
}

//=============================================================================
// 更新処理
//=============================================================================
void StageManager::Update(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->pObj->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void StageManager::Draw(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->pObj->Draw();
	}
}