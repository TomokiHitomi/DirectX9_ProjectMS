#include "main.h"
#include <assimp\scene.h>

class CSkinAssimp
{
private:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 uv;
		//D3DXVECTOR4 boneId;
		//D3DXVECTOR4 boneWeight;
	}VERTEX_ASSIMP;

	LPDIRECT3DTEXTURE9*				pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9*		pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9*			pIdxBuff;	// �C���f�b�N�X�o�b�t�@

	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// ���_�錾

	//D3DXMATRIX						mtxWorld;	// ���[���h�s��

	// �V�F�[�_�[�֘A
	LPD3DXEFFECT					pEffect;

	unsigned int nMeshCount;

	unsigned int* pVtxCount;
	unsigned int* pFaceCount;

public:
	CSkinAssimp();
	~CSkinAssimp();
	HRESULT Init(void);
	void Update(void);
	void Draw(D3DXMATRIX mtxWorld);
	void Release(void);

private:
	void CSkinAssimp::SearchNode(aiNode* node, const aiScene* scene);
	void CSkinAssimp::ProcessNode(aiNode* node, const aiScene* scene);
	void CSkinAssimp::ProcessMesh(aiMesh* mesh, const aiScene* scene);
};


