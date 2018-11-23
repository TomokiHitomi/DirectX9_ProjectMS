//=============================================================================
//
// X�t�@�C���V�F�[�_ [xmodel.fx]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
float4x4	world;		// ���[���h�}�g���N�X
float4x4	view;		// �r���[�}�g���N�X
float4x4	proj;		// �v���W�F�N�V�����}�g���N�X
float4		eye;		// ���_���W

// ���C�g
typedef struct _LIGHT
{
	float4		dif;	// �g�U��
	float4		amb;	// ����
	float4		spc;	// ���ˌ�
	float3		pos;	// ���W
	float3		dir;	// ���s����
}LIGHT;

// �}�e���A��
typedef struct _MATERIAL
{	// D3DMATERIAL9�Ɠ�������
	float4		dif;	// �g�U��
	float4		amb;	// ����
	float4		spc;	// ���ˌ�
	float4		emi;	// ������
	float		pwr;	// ���ˌ��̃p���[�l
}MATERIAL;


LIGHT		lt;
MATERIAL	mat;

// �e�N�X�`��
texture tex;
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
	float3	nor : NORMAL;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;
	float4	spc : TEXCOORD1;
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
	Out.nor = mul(In.nor, (float3x3)world);

	float3	N = 0.0f;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L = 0.0f;		// ���̍������ޕ���
	float3	P = 0.0f;		// ���[���h��ԏ�̒��_���W
	float3	V = 0.0f;		// �i�J�������W�[���_���W�j�x�N�g��
	float3  H = 0.0f;		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j

	P = Out.pos.xyz;

	N = normalize(Out.nor);

	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(-lt.dir);

	// �����x�N�g�������߂�
	V = normalize(eye.xyz - P);

	// ���x�N�g���Ǝ����Ƃ̃n�[�t�x�N�g�������߂�
	H = normalize(L + V);

	// �����v�Z���s���ďo�̓J���[�����߂�
	Out.col = mat.emi +
		lt.amb * mat.amb +
		lt.dif * mat.dif *
		max(0.0f, dot(N, L));	// 0.0�����̏ꍇ��0.0��

	Out.col.a = mat.dif.a;

	// �X�y�L�����[�ɂ�锽�ːF���v�Z�@g_power���傫���قǉs������
	Out.spc = lt.spc * mat.spc *
		pow(max(0.0f, dot(N, H)), mat.pwr);



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

	// �����v�Z���s���ďo�̓J���[�����߂�
	Out.col = saturate(mat.emi + mat.amb + mat.dif);	// 0.0�����̏ꍇ��0.0��

	Out.col.a = mat.dif.a;

	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_light_on_tex(VS_OUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(In.col * tex2D(smp, In.uv) + In.spc);
	out_color.a = In.col.a;
	return out_color; 
}

float4 ps_light_off_tex(VS_OUT In) : COLOR0
{
	return tex2D(smp, In.uv);
}

float4 ps_light_on(VS_OUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(In.col + In.spc);
	out_color.a = In.col.a;
	return out_color;
}

float4 ps_light_off(VS_OUT In) : COLOR0
{
	return In.col;
}


//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique LIGHT_ON_TEX
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_on();
		PixelShader = compile ps_3_0 ps_light_on_tex();
	}
}

technique LIGHT_OFF_TEX
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_off();
		PixelShader = compile ps_3_0 ps_light_off_tex();
	}
}

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