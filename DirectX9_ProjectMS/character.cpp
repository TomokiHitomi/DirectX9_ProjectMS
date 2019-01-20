//=============================================================================
//
// キャラクター処理 [character.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "character.h"
#include "player.h"

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
		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] = new CSkinMesh;
		}
	}

	if (CharacterManager::m_bUse)
	{
		m_CSkinMesh[FIREMAN]->Init(pDevice, CHARACTER_FIREMAN);
		m_CSkinMesh[DOCTOR]->Init(pDevice, CHARACTER_DOCTOR);
		m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
		m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);

		//m_CSkinMesh[PASTRY]->Init(pDevice, CHARACTER_PASTRY);
		//m_CSkinMesh[IDOL]->Init(pDevice, CHARACTER_IDOL);
	}

	// ループしないアニメーションを指定
	for (unsigned int i = 0; i < TYPE_MAX; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
		{
			m_CSkinMesh[i]->LoopAnim(Player::JUMP_START, false, j);

			m_CSkinMesh[i]->LoopAnim(Player::ATK_LEFT, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_RIGHT, false, j);

			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP1, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP2, false, j);
			m_CSkinMesh[i]->LoopAnim(Player::ATK_SP3, false, j);
		}
	}
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
	if (CharacterManager::m_bUse)
	{
		return m_CSkinMesh[etype];
	}
	else
	{
		return NULL;
	}

}