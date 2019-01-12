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
#define RESULTCHARCTER_POS_MARGIN	(30.0f)
#define RESULTCHARCTER_CAMERA_EYE	(D3DXVECTOR3(0.0f, 10.0f, 0.0f))
#define RESULTCHARCTER_CAMERA_AT1	(D3DXVECTOR3(-10.0f, 5.0f, -15.0f))
#define RESULTCHARCTER_CAMERA_AT2	(D3DXVECTOR3(10.0f, 5.0f, -15.0f))

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultCharacterManager : public ObjectManager
{
private:
	enum
	{
		RESULT_WIN,
		RESULT_LOSE,
		RESULT_MAX
	};
	CSkinMesh	*m_CSkinMesh[RESULT_MAX];	// スキンメッシュ格納用
	D3DXVECTOR3	vPos[RESULT_MAX];
	D3DXVECTOR3	vScl[RESULT_MAX];
	D3DXVECTOR3	vRot[RESULT_MAX];
	D3DXMATRIX mtxWorld[RESULT_MAX];


public:
	// コンストラクタ（初期化処理）
	ResultCharacterManager(void);
	//デストラクタ（終了処理）
	~ResultCharacterManager(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	float SearchScl(int nChar);
	static bool m_bUse;

private:
	D3DXVECTOR3 SetScl(float scl) { return D3DXVECTOR3(scl, scl, scl); }
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
