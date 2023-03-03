#include "VertexShaderInputType.hlsli"
#include "CameraBuffer.hlsli"
#include "ObjectBuffer.hlsli"
#include "MaterialBuffer.hlsli"
#include "AnimationBuffer.hlsli"
#include "MeshBuffer.hlsli"
#include "VertexShaderOutput.hlsli"

VertexOutput_PCNT_P VS(Vertex_PCNTs input)
{
	VertexOutput_PCNT_P output = (VertexOutput_PCNT_P)0;

	float4 pos = 0;
	float4 normal = 0;
	{
		pos = mul(input.Position, MeshAnimationMatrix[MeshIndex]);
		normal = mul(input.Normal, MeshAnimationMatrix[MeshIndex]);
	}

	float4 world = mul(pos, WorldTransformMatrix);
	float4 view = mul(world, ViewMatrix);
	float4 proj = mul(view, ProjectionMatrix);

	output.p = proj;
	output.n = normal;
	output.c = input.Color;
	output.t = input.Diffuse;
	output.param[0] = input.MaterialIndex;

	return output;
	
}
