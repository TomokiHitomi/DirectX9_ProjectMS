//=============================================================================
//
// �v���[���V�F�[�_ [plane.fx]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
float4x4	world;		// ���[���h�}�g���N�X
float4x4	view;		// �r���[�}�g���N�X
float4x4	proj;		// �v���W�F�N�V�����}�g���N�X
float		color;

texture tex;			// �g�p����e�N�X�`��
sampler smp = sampler_state {
	texture = <tex>;
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct VS_IN		// ���_�V�F�[�_�̈���
{
	//float3 pos : POSITION;
	//float4 col : COLOR0;

	float4	pos : POSITION;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;
	float3	worldPos : TEXCOORD1;
};

struct VS_OUT		// ���_�V�F�[�_�̖߂�l���s�N�Z���V�F�[�_�[�̈���
{
	float4 pos : POSITION;
	float4 col : COLOR0;
	float2 uv : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUT vs_main( VS_IN In )
{
	//VS_OUT Out = (VS_OUT)0;
	VS_OUT Out;

	Out.pos = float4(
		In.pos.x,
		In.pos.y,
		In.pos.z,
		1.0f
	);

	Out.pos = mul(Out.pos, world);

	Out.pos = float4(
		Out.pos.x + In.worldPos.x,
		Out.pos.y + In.worldPos.y,
		Out.pos.z + In.worldPos.z,
		1.0f
		);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, proj);

	//mat = mul(mul(world, view), proj);
	//Out.pos = mul( float4(In.pos, 1.0f), mat );
	Out.uv  = In.uv;
	Out.col = In.col;
	Out.col.y = Out.col.y + color;
	Out.col.z = Out.col.z + color / 2.0;
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_nomal(VS_OUT In) : COLOR0
{
	return tex2D( smp, In.uv ) * In.col;
	//return tex2D(smp, In.uv);
}
technique Tec01		// �e�N�X�`���`��
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_nomal();
	}
}