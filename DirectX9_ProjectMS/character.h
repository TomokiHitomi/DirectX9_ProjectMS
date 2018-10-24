//=============================================================================
//
// キャラクター処理 [character.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "SkinMeshX.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHARACTER_FIREMAN			("data/MODEL/hackadollMMD.x")
#define CHARACTER_DOCTOR			("data/MODEL/Yuko.x")

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CharacterManager
{
public:
	enum TYPE
	{	// プレイヤー管理
		FIREMAN,
		DOCTOR,
		PASTRY,
		IDOL,
		TYPE_MAX
	};
	CSkinMesh	*m_CSkinMesh[TYPE_MAX];	// スキンメッシュ格納用

public:
	// コンストラクタ（初期化処理）
	CharacterManager(void);
	//デストラクタ（終了処理）
	~CharacterManager(void);
	CSkinMesh *GetCharData(CharacterManager::TYPE);
private:
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
