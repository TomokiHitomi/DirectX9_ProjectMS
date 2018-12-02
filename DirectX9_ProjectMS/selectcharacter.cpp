//=============================================================================
//
// セレクトキャラクター処理 [selectcharacter.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "selectcharacter.h"
#include "scene.h"
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
//bool CharacterManager::m_bUse = true;

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
SelectCharacterManager::SelectCharacterManager(void)
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::SELECTCHARACTER, Priority::Middle, Priority::Middle);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		m_CSkinMesh[i] = NULL;
		vPos[i] = ZERO_D3DXVECTOR3;
		vPos[i].x = i * SELECTCHARCTER_POS_MARGIN - SELECTCHARCTER_POS_MARGIN * 2;

		vRot[i] = ZERO_D3DXVECTOR3;

		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] =
				SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)i);
		}
	}
	Init();
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
SelectCharacterManager::~SelectCharacterManager(void)
{
	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		//if(!m_CSkinMesh[i])
		//delete m_CSkinMesh[i];
		m_CSkinMesh[i] = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
void SelectCharacterManager::Init(void)
{
	// 各モデルのスケールを設定
	vScl[CharacterManager::FIREMAN] = SetScl(CHARACTER_FIREMAN_SCL);
	vScl[CharacterManager::PASTRY] = SetScl(CHARACTER_PASTRY_SCL);
	vScl[CharacterManager::IDOL] = SetScl(CHARACTER_IDOL_SCL);
	vScl[CharacterManager::DOCTOR] = SetScl(CHARACTER_DOCTOR_SCL);

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		WorldConvert(&mtxWorld[i], vPos[i], vRot[i], vScl[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SelectCharacterManager::Update(void)
{
	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL)
		{
			m_CSkinMesh[i]->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SelectCharacterManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		m_CSkinMesh[i]->Draw(pDevice, mtxWorld[i]);
	}
}


////=============================================================================
//// キャラクターデータの取得処理
////=============================================================================
//CSkinMesh *CharacterManager::GetCharData(CharacterManager::TYPE etype)
//{
//	if (CharacterManager::m_bUse)
//	{
//		return m_CSkinMesh[etype];
//	}
//	else
//	{
//		return NULL;
//	}
//
//}