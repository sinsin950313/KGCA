#include "VertexShaderStageBufferData.hlsli"

VS_out VS(VS_in input)
{
	VS_out output = (VS_out)0;

	float4 pos = 0;
	float4 normal = 0;
	{
		pos = mul(input.p, AnimatedMeshMatrix[MeshIndex]);
		normal = mul(input.n, AnimatedMeshMatrix[MeshIndex]);
	}
	for (int i = 0; i < 4; ++i)
	{
		int index = input.AffectingBoneIndex[i];
		float weight = input.Weight[i];
		matrix toBoneSpaceMatrix = BoneSpaceTransform[index];
		matrix boneAnimationMatrix = AnimatedBoneMatrix[index];

		float4 tmpPos = mul(input.p, toBoneSpaceMatrix);
		pos += mul(tmpPos, boneAnimationMatrix) * weight;

		float4 tmpNormal = mul(input.n, toBoneSpaceMatrix);
		normal += mul(tmpNormal, boneAnimationMatrix) * weight;
	}

	float4 world = mul(pos, World);
	float4 view = mul(world, View);
	float4 proj = mul(view, Projection);

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
	return float4(1, 0, 0, 1);
	//return g_txTextureA.Sample(g_sampleA, input.t);
	//return input.n;
}
