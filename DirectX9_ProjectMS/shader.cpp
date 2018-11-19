//=============================================================================
//
// �V�F�[�_���� [shader.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "shader.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
D3DXVECTOR4 ShaderColorToVec(D3DCOLORVALUE color);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Shader* ShaderManager::pShader[FILE_MAX];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ShaderManager::ShaderManager()
{
	for (unsigned int i = 0; i < FILE_MAX; i++)
	{
		pShader[i] = NULL;
	}

	// ����������
	Load();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ShaderManager::~ShaderManager()
{
	// �폜����
	Delete();
}

//=============================================================================
// �ǂݍ��ݏ���
//=============================================================================
HRESULT ShaderManager::Load(void)
{
	pShader[BILLBOARD] = new Shader(SHADER_FILE_BILLBOARD);
	pShader[XMODEL] = new Shader(SHADER_FILE_XMODEL);
	pShader[SKINMESH] = new Shader(SHADER_FILE_SKINMESH);
	pShader[PLANE] = new Shader(SHADER_FILE_PLANE);
	pShader[BOX] = new Shader(SHADER_FILE_BOX);
	return S_OK;
}

//=============================================================================
// �폜����
//=============================================================================
void ShaderManager::Delete(void)
{
	for (unsigned int i = 0; i < FILE_MAX; i++)
	{
		SAFE_DELETE(pShader[i]);
	}
}

////=============================================================================
//// �X�V����
////=============================================================================
//void ShaderManager::Update(void)
//{
//	//SAFE_UPDATE();
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void ShaderManager::Draw(void)
//{
//	//SAFE_DRAW();
//}



//=============================================================================
// �R���X�g���N�^
//=============================================================================
Shader::Shader(const char* path)
{
	// �V�F�[�_�֘A�̏�����
	pErrorBuff = NULL;	// �V�F�[�_�p�R���p�C���G���[
	pEffect = NULL;		// �V�F�[�_
	numPass = 0;		// �p�X��������

	// ����������
	Init(path);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Shader::~Shader()
{
	// �������
	Release();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Shader::Init(const char* path)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �t�@�C��( const char* path )����V�F�[�_�[�t�@�C����ǂݍ��ݓǂݍ���
	if (FAILED(D3DXCreateEffectFromFile(
		pDevice, path, 0, 0, 0, 0, &pEffect, &pErrorBuff)))
	{
		// �G���[
		MessageBox(NULL, (LPCTSTR)pErrorBuff->GetBufferPointer(), path, MB_OK);
		return S_FALSE;
	}
	return S_OK;
}

//=============================================================================
// �������
//=============================================================================
void Shader::Release(void)
{
	// �������
	SAFE_RELEASE(pErrorBuff);	// �V�F�[�_�p�R���p�C���G���[
	SAFE_RELEASE(pEffect);		// �V�F�[�_
}

////=============================================================================
//// �X�V����
////=============================================================================
//void Shader::Update(void)
//{
//
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void Shader::Draw(void)
//{
//
//}

//=============================================================================
// ����
//=============================================================================
D3DXVECTOR4 ShaderColorToVec(D3DCOLORVALUE color)
{
	D3DXVECTOR4 temp;
	temp.x = color.r;
	temp.y = color.g;
	temp.z = color.b;
	temp.w = color.a;
	return temp;
}

//=============================================================================
// ����
//=============================================================================
void SetShaderMat(LPD3DXEFFECT pEffect, D3DMATERIAL9 pMat)
{
	if (FAILED(pEffect->SetValue("mat", &pMat, sizeof(D3DMATERIAL9))))
	{
		MessageBox(NULL, "�Ă���", "mat", MB_OK);
		//return E_FAIL;
	}

	D3DXVECTOR4  temp;

	// �f�B�t���[�Y���p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pMat.Diffuse);
	pEffect->SetVector("dif_mat", &temp);

	// �����p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pMat.Ambient);
	pEffect->SetVector("amb_mat", &temp);

	// �G�~�b�V�u���p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pMat.Emissive);
	pEffect->SetVector("emi_mat", &temp);

	// �X�y�L�����[���p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pMat.Specular);
	pEffect->SetVector("spc_mat", &temp);

	// �p���[�l���Z�b�g
	pEffect->SetFloat("pwr_mat", pMat.Power);
}

//=============================================================================
// ����
//=============================================================================
void SetShaderLight(LPD3DXEFFECT pEffect, D3DLIGHT9 pLight)
{
	D3DXVECTOR4  temp;
	// �����p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pLight.Ambient);
	pEffect->SetVector("amb_lt", &temp);

	// �f�B�t���[�Y���p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pLight.Diffuse);
	pEffect->SetVector("dif_lt", &temp);

	// �X�y�L�����[���p�̃}�e���A�����Z�b�g
	temp = ShaderColorToVec(pLight.Specular);
	pEffect->SetVector("spc_lt", &temp);

	// ���C�g�̃x�N�g�����Z�b�g
	temp = D3DXVECTOR4(pLight.Direction, 0.0f);
	pEffect->SetVector("dir_lt", &temp);
}