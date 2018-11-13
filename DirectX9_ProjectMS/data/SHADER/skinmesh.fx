//=============================================================================
//
// �X�L�����b�V���V�F�[�_ [skinmesh.fx]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
float4x4	world;		// ���[���h�}�g���N�X
float4x4	view;		// �r���[�}�g���N�X
float4x4	proj;		// �v���W�F�N�V�����}�g���N�X
float3		ld;			// ���C�g�x�N�g��

// ���C�g
float4		dif_lt;		// �f�B�t���[�Y
float4		amb_lt;		// ����
float4		spc_lt;		// �X�y�L�����[��
float3		dir_lt;		// ���s�����̕���

// �}�e���A��
float4		dif_mat;	// �f�B�t���[�Y��
float4		emi_mat;	// �G�~�b�V�u��
float4		amb_mat;	// ����
float4		spc_mat;	// �X�y�L�����[
float		pwr_mat;	// �X�y�L�����[���̃p���[�l

texture tex;			// �g�p����e�N�X�`��
sampler smp = sampler_state {
	texture = <tex>;
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct VS_IN		// ���_�V�F�[�_�̈���
{
	float3	pos : POSITION;
	float3	nor : NORMAL;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;

};

struct VS_OUT		// ���_�V�F�[�_�̖߂�l���s�N�Z���V�F�[�_�[�̈���
{
	float4	pos : POSITION;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUT vs_light_on( VS_IN In )
{
	VS_OUT Out = (VS_OUT)0;
	//VS_OUT Out;

	Out.pos = float4(
		In.pos.x,
		In.pos.y,
		In.pos.z,
		1.0f
	);

	Out.pos = mul(Out.pos, world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, proj);

	// �@�������[���h��Ԃ�
	float3 nor = mul(In.nor, world);

   // ���˂�����̋������Z�o
	//float Power = saturate(dot(normalize(nor), -normalize(dir_lt)));
	//Power = clamp(Power, 0.0f, 1.0f);

	// �����p�[�h����
	Out.col = dif_mat * dif_lt;
	Out.col = Out.col + amb_mat * amb_lt;
	Out.col = Out.col + emi_mat;


	// �X�y�L�������ˁi�������j
	//float4 spc_temp = float4(0.0f, 0.0f, 1.0f, 1.0f);
	float3 eyePos = float3(view._41, view._42, view._43);
	float3	V = normalize(eyePos - Out.pos);		// �i�J�������W�[���_���W�j�x�N�g��
	//float3	H = -normalize(V + dir_lt);		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j
	float3	R = normalize(2 * dot(dir_lt, nor) * nor - dir_lt);
	float specularLight = pow(saturate(dot(R, V)), 1.5f);
	//Out.col = Out.col + (spc_temp * specularLight);
	Out.col = Out.col + (spc_mat * specularLight);


	// ���˂�����̋������Z�o
	Out.col = Out.col * saturate(dot(normalize(nor), -normalize(dir_lt)));

	// ���l�͓��͒l�����̂܂܎g�p
	Out.col.a = dif_mat.a;

	// uv�͂��̂܂܎g�p
	Out.uv  = In.uv;

	return Out;
}

VS_OUT vs_light_off(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = float4(
		In.pos.x,
		In.pos.y,
		In.pos.z,
		1.0f
		);

	Out.pos = mul(Out.pos, world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, proj);

	Out.uv = In.uv;
	Out.col = In.col;
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_light_on(VS_OUT In) : COLOR0
{
	return tex2D(smp, In.uv) * In.col;
}

float4 ps_light_off(VS_OUT In) : COLOR0
{
	return tex2D(smp, In.uv);
}

//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique LIGHT_ON
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_on();
		PixelShader = compile ps_3_0 ps_light_on();
	}
}

technique LIGHT_OFF
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_off();
		PixelShader = compile ps_3_0 ps_light_off();
	}
}