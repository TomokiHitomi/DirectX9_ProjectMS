//=============================================================================
//
// キャラクター処理 [character.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "character.h"

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
bool CharacterManager::m_bUse = true;

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
CharacterManager::CharacterManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		m_CSkinMesh[i] = NULL;
		m_CSkinMesh[i] = new CSkinMesh;
	}

	m_CSkinMesh[FIREMAN]->Init(pDevice, CHARACTER_FIREMAN);
	m_CSkinMesh[DOCTOR]->Init(pDevice, CHARACTER_DOCTOR);
	//m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
	//m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
CharacterManager::~CharacterManager(void)
{
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		if(!m_CSkinMesh[i])
		delete m_CSkinMesh[i];
		m_CSkinMesh[i] = NULL;
	}
}

//=============================================================================
// キャラクターデータの取得処理
//=============================================================================
CSkinMesh *CharacterManager::GetCharData(CharacterManager::TYPE etype)
{
	return m_CSkinMesh[etype];
}