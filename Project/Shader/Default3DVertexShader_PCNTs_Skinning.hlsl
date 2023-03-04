#include "VertexShaderInputType.hlsli"
#include "CameraBuffer.hlsli"
#include "ObjectBuffer.hlsli"
#include "MaterialBuffer.hlsli"
#include "AnimationBuffer.hlsli"
#include "MeshBuffer.hlsli"
#include "VertexShaderOutputType.hlsli"

VertexOutput_PCNT_P VS(Vertex_PCNTs_Skinning input)
{
	VertexOutput_PCNT_P output = (VertexOutput_PCNT_P)0;

	float4 pos = 0;
	float4 normal = 0;
	for (int i = 0; i < 4; ++i)
	{
		int index = input.BoneIndex[i];
		float weight = input.Weight[i];
		matrix toBoneSpaceMatrix = ToBoneSpaceTransformMatrix[index];
		matrix boneAnimationMatrix = BoneAnimationMatrix[index];

		float4 tmpPos = mul(input.Position, toBoneSpaceMatrix);
		pos += mul(tmpPos, boneAnimationMatrix) * weight;

		float4 tmpNormal = mul(input.Normal, toBoneSpaceMatrix);
		normal += mul(tmpNormal, boneAnimationMatrix) * weight;
	}

	float4 world = mul(pos, WorldTransformMatrix);
	float4 view = mul(world, ViewMatrix);
	float4 proj = mul(view, ProjectionMatrix);

	output.p = proj;
	output.n = normal;
	output.c = input.Color;
	output.t = input.Diffuse;
	output.Index = input.MaterialIndex;

	return output;
}
