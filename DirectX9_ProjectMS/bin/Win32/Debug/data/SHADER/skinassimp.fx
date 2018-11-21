//=============================================================================
//
// Assimp���f���V�F�[�_ [skinassimp.fx]
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
	//float4	col : COLOR0;
	float2	uv : TEXCOORD0;

};

struct VS_OUT		// ���_�V�F�[�_�̖߂�l���s�N�Z���V�F�[�_�[�̈���
{
	float4	pos : POSITION;
	float3	nor : NORMAL;
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
	//float3 nor = mul(In.nor, world);
	Out.nor = mul(In.nor, world);

   // ���˂�����̋������Z�o
	//float Power = saturate(dot(normalize(nor), -normalize(dir_lt)));
	//Power = clamp(Power, 0.0f, 1.0f);

	//// �����p�[�h����
	//Out.col = mat.dif * lt.dif;
	//Out.col = Out.col + mat.amb * lt.amb;
	//Out.col = Out.col + mat.emi;


	//// �X�y�L�������ˁi�������j
	////float4 spc_temp = float4(0.0f, 0.0f, 1.0f, 1.0f);
	//float3 eyePos = float3(view._41, view._42, view._43);
	//float3	V = normalize(eyePos - Out.pos);		// �i�J�������W�[���_���W�j�x�N�g��
	////float3	H = -normalize(V + dir_lt);		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j
	//float3	R = normalize(2 * dot(lt.dir, Out.nor) * Out.nor - lt.dir);
	//float specularLight = pow(saturate(dot(R, V)), 1.5f);
	////Out.col = Out.col + (spc_temp * specularLight);
	//Out.col = Out.col + (mat.spc * specularLight);

	//// ���˂�����̋������Z�o
	//Out.col = Out.col * saturate(dot(normalize(Out.nor), -normalize(lt.dir)));

	//// ���l�͓��͒l�����̂܂܎g�p
	//Out.col.a = mat.dif.a;

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
	//Out.col = In.col;
	Out.col = float4(
		1.0f,
		1.0f,
		1.0f,
		1.0f
		);
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_light_on(VS_OUT In) : COLOR0
{
	//// ���_�@��
	//float3 N = normalize(In.nor.xyz);

	//// ���_���璸�_�̃x�N�g��
	//float3 V = normalize(eye.xyz - In.pos.xyz);

	//// ���C�g���W���璸�_�̃x�N�g���i����͕��s�����݂̂Ȃ̂�Dir����
	//float3 L = -normalize(lt.dir.xyz); /*normalize(lt.pos.xyz - In.pos.xyz);*/

	//// �n�[�t�x�N�g��	H = norm(norm(Cp - Vp) + Ldir)
	////float3 H = normalize(v + l);

	////float  P = mat.pwr;

	////// ���C�g���W���璸�_�܂ł̋��������߂�
	//////float  d = length(l);
	////// ���C�g���W���璸�_�̃x�N�g���𐳋K��
	////l = normalize(l);
	//// ���ˌ��̃x�N�g�����v�Z
	////float3 r = 2.0 * n * dot(n, l) - l;
	////float3 r = l + 2.0 * dot(-l, n) * n;
	////// �������ނ��v�Z�i����͎g��Ȃ��j
	////float  a = 1.0f;
	////a = saturate(1.0f / (pntLight.attenuate.x + pntLight.attenuate.y * d + pntLight.attenuate.z * d * d)); //����

	////float powTmp = pow(saturate(dot(r, v)), mat.pwr);
	////float powTmp = 1.0f;

	//// �������v�Z
	//float3 iA =										mat.amb.xyz * lt.amb.xyz;
	//// �g�U�����v�Z
	//float3 iD = saturate(dot(L, N)) *				mat.dif.xyz * lt.dif.xyz;
	//// ���ˌ����v�Z
	////float3 iS = powTmp * (mat.spc.xyz * lt.spc.xyz) * a;
	////float3 iS = pow(saturate(dot(r, v)), mat.pwr) * (mat.spc.xyz * lt.spc.xyz) * a;


	//// �X�y�L���� ���C�e�B���O	  = Cs * sum[Ls*(N.H)P*Atten*Spot]
	////float3 iS = mat.spc.xyz * (lt.spc.xyz * pow(dot(N, H), P));


	//float4 iColor = float4(iA + iD /*+ iS*/, 1.0f);

	//float4 texcolor = tex2D(smp, In.uv);
	////texcolor = iColor;
	////texcolor.x = iColor.x;
	//texcolor.xyz = texcolor.xyz * iColor.xyz;
	////color.xyz = color.xyz * (iA + iD + iS);

	//return saturate(texcolor);
	////return float4(saturate(iA + iD + iS), 1.0);
	//return tex2D(smp, In.uv) * In.col;
	return tex2D(smp, In.uv);

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