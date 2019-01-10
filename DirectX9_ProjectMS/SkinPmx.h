#include "main.h"

class CSkinPmx
{
private:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 uv;
		//D3DXVECTOR4 boneId;
		//D3DXVECTOR4 boneWeight;
	}VERTEX_PMX;

	LPDIRECT3DTEXTURE9*				pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9*		pVtxBuff;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9*			pIdxBuff;	// インデックスバッファ

	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// 頂点宣言

	//D3DXMATRIX						mtxWorld;	// ワールド行列

	// シェーダー関連
	LPD3DXEFFECT					pEffect;

	unsigned int nMeshCount;

	unsigned int* pVtxCount;
	unsigned int* pFaceCount;

public:
	CSkinPmx();
	~CSkinPmx();
	HRESULT Init(void);
	void Update(void);
	void Draw(D3DXMATRIX mtxWorld);
	void Release(void);

private:
};


