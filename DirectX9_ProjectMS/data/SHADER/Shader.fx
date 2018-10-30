//=============================================================================
//
// �V�F�[�_�[���� [Shader.fx]
// Author : GP12A295 25 �l���F��
//
// ���_�V�F�[�_�[�ɂ�郉�C�e�B���O�E�s�N�Z���V�F�[�_�[����
//
// �Q�l�FDirectX9�ł̏�ʃ��x���V�F�[�_�[����iHLSL�j
// http://www001.upp.so-net.ne.jp/y_yutaka/labo/directx/shader_hlsl.html
//
//=============================================================================


//**********************************//
//	�O���[�o���ϐ�					//
//**********************************//

//���[���h*�r���[*���e�ϊ��̍s��
float4x4 gWVPMatrix;

//�A���r�G���g�l
float4 gAmbient = { 0.2f,0.2f,0.2f,1.0f };

//��{�F
float4 gBaseColor = { 1.0f, 0.1f, 0.2f, 1.0f };

//�e�N�X�`��
texture gTexture0;

//----------------------//
//	���_�̓��͏��		//
//----------------------//
struct VS_INPUT
{
	float4 vPosition		: POSITION;			//���_���W
	float4 vNormal			: NORMAL;			//�@���x�N�g��
	float2 vTexCoords		: TEXCOORD0;		//�e�N�X�`��UV
	float4 vDiffuse         : COLOR0;			//�f�t���[�Y�F
	float4 vSpecular        : COLOR1;			//�X�y�L�����F
};

//----------------------//
//	���_�̏o�͏��		//
//----------------------//
struct VS_OUTPUT
{
	float4 vPosition		: POSITION;			//���_���W
	float4 vDiffuse			: COLOR0;			//�f�t���[�Y�F
	float4 vSpecular		: COLOR1;			//�X�y�L�����F
	float2 vTexCoords		: TEXCOORD0;		//�e�N�X�`��UV
};

//----------------------//
//	�s�N�Z���̓��͏��	//
//----------------------//
struct PS_INPUT
{
	float4 vDiffuse			: COLOR0;			//�f�t���[�Y�F
	float4 vSpecular		: COLOR1;			//�X�y�L�����F
	float2 vTexCoords		: TEXCOORD0;		//�e�N�X�`��UV
};

//----------------------//
//	�s�N�Z���̏o�͏��	//
//----------------------//
struct PS_OUTPUT
{
	float4 vColor			: COLOR0;			//�ŏI�I�ȏo�͐F
};


//**********************************************//
//	��{�F�݂̂��l���������_�E�s�N�Z���v�Z		//
//**********************************************//

VS_OUTPUT VSBaseColor(VS_INPUT v)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	//���W�ϊ�
	o.vPosition = mul(v.vPosition, gWVPMatrix);

	//�f�t���[�Y�F�����̂܂܊i�[
	o.vDiffuse = v.vDiffuse;

	//�X�y�L�����F�����̂܂܊i�[
	o.vSpecular = v.vSpecular;

	return o;
}

//���ӁI�I�s�N�Z���V�F�[�_�[���ł�
//max�Ȃǂ̑g�ݍ��݊֐��͎g���Ȃ��I�I�I

PS_OUTPUT PSBaseColor(PS_INPUT p)
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	o.vColor = (p.vDiffuse + gAmbient) * gBaseColor + p.vSpecular;

	return o;
}

//**********************************************//
//	�e�N�X�`�����l���������_�E�s�N�Z���v�Z		//
//**********************************************//

VS_OUTPUT VSTextureColor(const VS_INPUT v)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	//���W�ϊ�
	o.vPosition = mul(v.vPosition, gWVPMatrix);

	//�f�t���[�Y�F�����̂܂܊i�[
	o.vDiffuse = v.vDiffuse;

	//�X�y�L�����F�����̂܂܊i�[
	o.vSpecular = v.vSpecular;

	//�e�N�X�`���l
	o.vTexCoords = v.vTexCoords;

	return o;
}

//�e�N�X�`���̐��`��Ԃ̂��߂̃T���v���[���
sampler Sampler = sampler_state
{
	Texture = <gTexture0>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

PS_OUTPUT PSTextureColor(PS_INPUT p)
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 col;

	col = (p.vDiffuse + gAmbient);
	o.vColor = col * tex2D(Sampler, p.vTexCoords) + p.vSpecular;

	return o;
}

//**********************************************//
//	�e�N�j�b�N�̋L�q							//
//**********************************************//

//----------------------//
//	��{�F�̂̂�		//
//----------------------//
technique BaseColor
{
	pass P0
	{
		VertexShader = compile vs_2_0 VSBaseColor();
		PixelShader = compile ps_2_0 PSBaseColor();
	}
}

//----------------------//
//	�e�N�X�`������		//
//----------------------//
technique TextureColor
{
	pass P0
	{
		VertexShader = compile vs_2_0 VSTextureColor();
		PixelShader = compile ps_2_0 PSTextureColor();
	}
}
