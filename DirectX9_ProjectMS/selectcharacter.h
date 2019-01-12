//=============================================================================
//
// セレクトキャラクター処理 [selectcharacter.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _SELECTCHARACTER_H_
#define _SELECTCHARACTER_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "character.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECTCHARCTER_POS_MARGIN	(30.0f)
#define SELECTCHARCTER_CAMERA_EYE	(D3DXVECTOR3(0.0f, 10.0f, 0.0f))
#define SELECTCHARCTER_CAMERA_AT1	(D3DXVECTOR3(-10.0f, 5.0f, -15.0f))
#define SELECTCHARCTER_CAMERA_AT2	(D3DXVECTOR3(10.0f, 5.0f, -15.0f))

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SelectCharacterManager : public ObjectManager
{
public:

	CSkinMesh	*m_CSkinMesh[CharacterManager::TYPE_MAX];	// スキンメッシュ格納用
	D3DXVECTOR3	vPos[CharacterManager::TYPE_MAX];
	D3DXVECTOR3	vScl[CharacterManager::TYPE_MAX];
	D3DXVECTOR3	vRot[CharacterManager::TYPE_MAX];
	D3DXMATRIX mtxWorld[CharacterManager::TYPE_MAX];


public:
	// コンストラクタ（初期化処理）
	SelectCharacterManager(void);
	//デストラクタ（終了処理）
	~SelectCharacterManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	static bool m_bUse;

private:
	D3DXVECTOR3 SetScl(float scl) { return D3DXVECTOR3(scl, scl, scl); }
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
