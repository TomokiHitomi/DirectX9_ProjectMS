//=============================================================================
//
// シェーダ処理 [shader.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _SHADER_H_
#define _SHADER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADER_FILE_BILLBOARD	"data/SHADER/billboard.fx"
#define SHADER_FILE_XMODEL		"data/SHADER/xmodel.fx"
#define SHADER_FILE_SKINASSIMP	"data/SHADER/skinassimp.fx"
#define SHADER_FILE_SKINMESH	"data/SHADER/skinmesh.fx"
#define SHADER_FILE_PLANE		"data/SHADER/plane.fx"
#define SHADER_FILE_BOX			"data/SHADER/box.fx"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Shader
{
public:
	// シェーダー関連
	LPD3DXBUFFER					pErrorBuff;
	LPD3DXEFFECT					pEffect;

	Shader(const char* path);
	~Shader();

	HRESULT Init(const char* path);
	void Release(void);

	// エフェクト取得メソッド
	LPD3DXEFFECT GetEffect(void) { return pEffect; }
};

class ShaderManager
{
public:
	enum FILE
	{
		BILLBOARD,
		XMODEL,
		SKINASSIMP,
		SKINMESH,
		PLANE,
		BOX,
		FILE_MAX
	};
private:
	static Shader* pShader[FILE_MAX];
	static LPD3DXBUFFER	pErrorBuff;
public:
	ShaderManager();
	~ShaderManager();
	static HRESULT Load(void);
	static void Delete(void);
	// エフェクト取得メソッド
	static HRESULT CreateEffect(LPD3DXEFFECT* pEffect,FILE eFile);
	static LPD3DXEFFECT GetEffect(FILE eFile) { return pShader[eFile]->GetEffect(); }
};
//
//class ShaderProp
//{
//public:
//	// シェーダー関連
//	LPD3DXBUFFER					pErrorBuff;
//	LPD3DXEFFECT					pEffect;
//	UINT							numPass;
//
//	Shader(const char* path);
//	~Shader();
//
//	HRESULT Init(const char* path);
//	void Release(void);
//
//	// エフェクト取得メソッド
//	LPD3DXEFFECT GetEffect(void) { return pEffect; }
//};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetShaderMat(LPD3DXEFFECT pEffect, D3DMATERIAL9 pMat);
void SetShaderLight(LPD3DXEFFECT pEffect, D3DLIGHT9 pLight);

#endif