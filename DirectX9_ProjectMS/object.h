//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "main.h"
#include "XModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙型定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************

// オブジェクト用
class ObjectManager
{
public:
	// リスト内優先順位
	enum Priority
	{
		Highest,
		High,
		Middle,
		Low,
		Lowest
	};

	// オブジェクトID
	enum ObjectID
	{
		NON,
		COPYRIGHT,
		PLAYER,
		EFFECT,
		SKYDOME,
		CUBE,
		STENCIL,
		STAGE,
		SELECTFACE,
		TITLELOGO,
		TITLEMESH,
		GAGE,
		GAGE3D,
		RESULTSELECT,
		GRAY,
		GRAYKO,
		PARTICLE,
		RIGHTLEFT,
		KO,
		WINNERLOGO,
		ROUNDLOGO,
		TIME,
		TIMEUPLOGO,
		WEAPON
	};

	// オブジェクトタイプ
	enum ObjectType
	{
		NORMAL,
		UI
	};

	// ルートポインタ
	enum ObjectRoot
	{
		UpdateRoot,
		DrawRoot,
		ObjectRootMax
	};

private:
	static int				nObjectCount;					// 全オブジェクト数のカウンタ
	static ObjectManager	*s_pRoot[ObjectRootMax];		// リストの更新ルートポインタ
	ObjectManager			*m_pPrev[ObjectRootMax];		// リストの前ポインタ
	ObjectManager			*m_pNext[ObjectRootMax];		// リストの次ポインタ
	Priority				m_ePriority[ObjectRootMax];		// 優先順位（サブ）
	ObjectID				eObjectId;						// オブジェクト識別用ID
	ObjectType				eObjectType;					// オブジェクトタイプ

public:
	// コンストラクタ（初期化処理）
	ObjectManager();
	// デストラクタ（終了処理）
	virtual ~ObjectManager();

	// 更新処理
	virtual void Update(void) { ; }
	// 描画処理
	virtual void Draw(void) { ; }
	// 解放処理
	void Release(void);

	// オブジェクトIDとプライオリティの設定処理
	void SetIdAndPriority(ObjectID, Priority, Priority);
	// オブジェクトのリスト追加処理
	void InsertList(void);
	// オブジェクトのリスト離脱処理
	void RemoveList(void);

	// 全オブジェクトの更新処理
	static void UpdateAll(void);
	// 全オブジェクトの描画処理
	static void DrawAll(void);
	// 全オブジェクトの解放処理
	static void ReleaseAll(void);

	// 通常オブジェクトの描画処理
	static void DrawNormalAll(void);
	// UIオブジェクトの描画処理
	static void DrawUiAll(void);


	// ルートポインタの取得処理
	static ObjectManager *GetObjectRoot(ObjectRoot eObjRoot) { return s_pRoot[eObjRoot]; }
	// ルートポインタのアドレス取得処理
	static ObjectManager **GetObjectRootAdr(ObjectRoot);

	// ネクストポインタの取得処理
	ObjectManager *GetObjectNext(ObjectRoot eObjRoot);


	// オブジェクトID設定処理
	void SetObjectId(ObjectID eObjId) { eObjectId = eObjId; }
	// オブジェクトID取得処理
	ObjectID GetObjectId(void) { return (eObjectId); }

	// オブジェクトタイプ設定処理
	void SetObjectType(ObjectType eObjType) { eObjectType = eObjType; }
	// オブジェクトタイプ取得処理
	ObjectType GetObjectType(void) { return (eObjectType); }

	// プライオリティ設定処理
	void SetPriority(ObjectRoot eObjRoot, Priority ePriority) { m_ePriority[eObjRoot] = ePriority; }
	// プライオリティ取得処理
	Priority GetPriority(ObjectRoot eObjRoot) { return (m_ePriority[eObjRoot]); }

	// オブジェクトのポインタ取得処理
	template <typename Type>
	static Type *GetObjectPointer(ObjectID eObjId)
	{
		ObjectManager *pList = GetObjectRoot(UpdateRoot);

		while (pList != NULL)
		{
			if (eObjId == pList->GetObjectId())
			{
				// 対象ポインタを指定した型でダウンキャストして返す
				return dynamic_cast<Type*>(pList);
			}
			pList = pList->GetObjectNext(UpdateRoot);
		}
		return NULL;
	}

	// オブジェクトの作成処理
	template <typename Type>
	static void CreateObject(void)
	{
		new Type;
	}
};

class Object
{
public:
	int					nNum;
	struct Prop
	{
		CXModel			*CXModel;			// モデル格納用
		D3DXVECTOR3		vPos;				// 座標情報
		D3DXVECTOR3		vRot;				// 回転情報
		D3DXVECTOR3		vScl;				// 拡縮情報
		D3DXMATRIX		mtxWorld;			// ワールドマトリクス
		bool			bUse;
	}*prop;
	
	// 更新処理
	virtual void Update(void) { ; }
	// 描画処理
	void Draw(void);
	// 解放処理
	void Delete(int num);

	// コンストラクタ
	Object(void) { ; }
	Object(int num)
	{
		nNum = num;
		prop = new Prop[num];
		// 各プロパティの初期化
		for (unsigned int i = 0; i < nNum; i++)
		{
			prop[i].vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			prop[i].vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			prop[i].vScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			prop[i].CXModel = new CXModel;
			prop[i].bUse = true;
		}
	}
	// デストラクタ
	~Object()
	{
		for (unsigned int i = 0; i < nNum; i++)
		{
			if (prop[i].CXModel != NULL)
			{
				prop[i].CXModel->Release();
				delete prop[i].CXModel;
			}
		}
		delete prop;
	}
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
