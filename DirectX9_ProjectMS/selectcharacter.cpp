//=============================================================================
//
// セレクトキャラクター処理 [selectcharacter.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "selectcharacter.h"
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
		vPos[i].x = (i * SELECTCHARCTER_POS_MARGIN) - ((CharacterManager::TYPE_MAX - 1) * SELECTCHARCTER_POS_MARGIN / 2);

		vRot[i] = D3DXVECTOR3(0.0f, -0.35f, 0.0f);

		if (CharacterManager::m_bUse)
		{
			m_CSkinMesh[i] =
				SceneManager::GetCharMgr()->GetCharData((CharacterManager::TYPE)i);
			if (m_CSkinMesh[i])
			{
				m_CSkinMesh[i]->ChangeAnim(Player::IDOL, 1.0f, 0);
				m_CSkinMesh[i]->ChangeAnim(Player::IDOL, 1.0f, 1);

				//m_CSkinMesh[i]->LoopAnim(Player::IDOL, false, 0);
				//m_CSkinMesh[i]->LoopAnim(Player::IDOL, false, 1);
			}
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

	// カメラ慣性を設定
	Camera* pCamera;
	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		pCamera = CameraManager::GetCamera((CameraManager::CameraType)i);
		pCamera->SetAtIner(0.3f);
		pCamera->SetEyeIner(0.1f);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SelectCharacterManager::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("【　SelectCharacter　】\n");
#endif



	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_LEFT))vRot[i].y += 0.1f;
		if (GetKeyboardTrigger(DIK_RIGHT))vRot[i].y -= 0.1f;
		PrintDebugProc("rot[%f] \n", vRot[i].y);
#endif
		WorldConvert(&mtxWorld[i], vPos[i], vRot[i], vScl[i]);
	}

	int nSelectChar;
	for (unsigned int i = 0; i < PlayerManager::PLAYER_MAX; i++)
	{
		nSelectChar = SearchCharSelect(i);

		for (unsigned int j = 0; j < CharacterManager::TYPE_MAX; j++)
		{
			if (m_CSkinMesh[j] != NULL) m_CSkinMesh[j]->Update(i);
		}

		// カメラをAtをセット
		CameraManager::pCamera[i]->SetAt(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_EYE);

		// カメラEyeをセット
		if		(i == 0) CameraManager::pCamera[i]->SetEye(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_AT1);
		else if	(i == 1) CameraManager::pCamera[i]->SetEye(vPos[nSelectChar] + SELECTCHARCTER_CAMERA_AT2);


#ifdef _DEBUG
		PrintDebugProc("Player%d:[%d] \n",i, nSelectChar);
#endif
	}



	//for (unsigned int j = 0; j < CharacterManager::TYPE_MAX; j++)
	//{



	//}
#ifdef _DEBUG
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void SelectCharacterManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCameraType = (int)CameraManager::GetType();

	for (unsigned int i = 0; i < CharacterManager::TYPE_MAX; i++)
	{
		if (m_CSkinMesh[i] != NULL)
		m_CSkinMesh[i]->Draw(pDevice, mtxWorld[i], nCameraType);
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