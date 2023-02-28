struct VS_in
{
	float4 p : Position;
	float4 n : Normal;
	float4 c : Color;
	float2 t : Texture;
	int4 AffectingBoneIndex : AffectingBoneIndex;
	float4 Weight : Weight;
};

cbuffer Camera : register(b0)
{
	matrix g_World : packoffset(c0);
	matrix g_View : packoffset(c4);
	matrix g_Projection : packoffset(c8);
};

cbuffer Object : register(b1)
{
	matrix AnimatedBoneMatrix[255];
	matrix AnimatedMeshMatrix[255];
}

cbuffer MeshData : register(b2)
{
	matrix ToBoneSpace[255];
	float4 MeshParam;
}

struct VS_out
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_out VS(VS_in input)
{
	VS_out output = (VS_out)0;

	float4 pos = 0;
	float4 normal = 0;
	{
		float index = MeshParam[0];
		float weight = MeshParam[1];
		pos = mul(input.p, AnimatedMeshMatrix[index]) * weight;
		normal = mul(input.n, AnimatedMeshMatrix[index]) * weight;
	}
	for (int i = 0; i < 4; ++i)
	{
		int index = input.AffectingBoneIndex[i];
		float weight = input.Weight[i];
		matrix toBoneSpaceMatrix = ToBoneSpace[index];
		matrix boneAnimationMatrix = AnimatedBoneMatrix[index];

		float4 tmpPos = mul(input.p, toBoneSpaceMatrix);
		pos += mul(tmpPos, boneAnimationMatrix) * weight;

		float4 tmpNormal = mul(input.n, toBoneSpaceMatrix);
		normal += mul(tmpNormal, boneAnimationMatrix) * weight;
	}

	float4 world = mul(pos, g_World);
	float4 view = mul(world, g_View);
	float4 proj = mul(view, g_Projection);

	output.p = proj;
	output.n = normal;
	output.c = input.c;
	output.t = input.t;

	return output;
}

Texture2D g_txTextureA : register(t0);
Texture2D g_txTexMaskA : register(t1);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 PS(PS_input input) : SV_TARGET
{
	//return float4(0, 0, 0, 1);
	return g_txTextureA.Sample(g_sampleA, input.t);
	//return input.n;
}
