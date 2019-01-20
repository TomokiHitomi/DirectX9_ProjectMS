//=============================================================================
//
// セレクトキャラクター処理 [selectcharacter.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "resultcharacter.h"
#include "selectface.h"
#include "scene.h"
#include "calculate.h"
#include "player.h"
#include "camera.h"
#include "input.h"

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
ResultCharacterManager::ResultCharacterManager(void)
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::RESULTCHARACTER, Priority::Middle, Priority::Middle);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nWin = SceneManager::GetWinPlayer();
	m_nCount = 0;

	for (unsigned int i = 0; i < RESULT_MAX; i++)
	{
		m_CSkinMesh[i] = NULL;
		vPos[i] = ZERO_D3DXVECTOR3;
		vPos[i].x = (i * RESULTCHARCTER_POS_MARGIN) - ((RESULT_MAX - 1) * RESULTCHARCTER_POS_MARGIN / 2);
		//vPos[i].x *= -1.0f;
		vRot[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (CharacterManager::m_bUse)
	{
		int nWinSelect = SceneManager::GetSelectChar(nWin);
		m_CSkinMesh[RESULT_WIN] =
			SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)nWinSelect);
		m_CSkinMesh[RESULT_WIN]->ChangeAnim(Player::IDOL, 1.0f, 0);
		vScl[RESULT_WIN] = SetScl(SearchScl(nWinSelect));

		int nLoseSelect = SceneManager::GetSelectChar(1 - nWin);
		m_CSkinMesh[RESULT_LOSE] =
			SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)nLoseSelect);
		m_CSkinMesh[RESULT_LOSE]->ChangeAnim(Player::IDOL, 1.0f, 1);
		vScl[RESULT_LOSE] = SetScl(SearchScl(nLoseSelect));


	}


	Init();
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
ResultCharacterManager::~ResultCharacterManager(void)
{
	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		//if(!m_CSkinMesh[i])
		//delete m_CSkinMesh[i];
		m_CSkinMesh[i] = NULL;
	}
}

//=============================================================================
// キャラサイズの取得
//=============================================================================
float ResultCharacterManager::SearchScl(int nChar)
{
	switch ((CharacterManager::TYPE)nChar)
	{
	case CharacterManager::FIREMAN:
		return (CHARACTER_FIREMAN_SCL);
		break;
	case CharacterManager::PASTRY:
		return (CHARACTER_PASTRY_SCL);
		break;
	case CharacterManager::IDOL:
		return (CHARACTER_IDOL_SCL);
		break;
	case CharacterManager::DOCTOR:
		return (CHARACTER_DOCTOR_SCL);
		break;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
void ResultCharacterManager::Init(void)
{
	for (unsigned int i = 0; i < RESULT_MAX; i++)
	{
		WorldConvert(&mtxWorld[i], vPos[i], vRot[i], vScl[i]);
	}

	// カメラ慣性を設定
	Camera* pCamera;
	pCamera = CameraManager::GetCamera(CameraManager::SINGLE);
	pCamera->SetAtIner(0.3f);
	pCamera->SetEyeIner(0.1f);

	// カメラをAtをセット
	pCamera->SetAt(vPos[RESULT_WIN] + RESULTCHARCTER_CAMERA_AT);

	// カメラEyeをセット
	pCamera->SetEye(vPos[RESULT_WIN] + RESULTCHARCTER_CAMERA_EYE);
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultCharacterManager::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("【　ResultCharacter　】\n");
#endif

	for (unsigned int i = 0; i < RESULT_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL) m_CSkinMesh[i]->Update(i);
	}

	m_nCount++;
	if (m_nCount == RESULTCHARCTER_STARTANIM)
	{
		int nWin = SceneManager::GetWinPlayer();

		switch (SceneManager::GetSelectChar(nWin))
		{
		case 0:
			m_CSkinMesh[RESULT_WIN]->ChangeAnim(Player::ATK_SP1, 1.0f, RESULT_WIN);
			break;
		case 1:
			m_CSkinMesh[RESULT_WIN]->ChangeAnim(Player::ATK_SP3, 1.0f, RESULT_WIN);
			break;
		case 2:
			m_CSkinMesh[RESULT_WIN]->ChangeAnim(Player::ATK_SP2, 1.0f, RESULT_WIN);
			break;
		case 3:
			m_CSkinMesh[RESULT_WIN]->ChangeAnim(Player::GUARD_SP1, 1.0f, RESULT_WIN);
			break;
		}

		m_CSkinMesh[RESULT_LOSE]->ChangeAnim(Player::DOWN, 1.0f, RESULT_LOSE);

	}

#ifdef _DEBUG
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultCharacterManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < RESULT_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL)
		m_CSkinMesh[i]->Draw(pDevice, mtxWorld[i], i);
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