#include "VertexShaderInputType.hlsli"
#include "CameraBuffer.hlsli"
#include "ObjectBuffer.hlsli"
#include "MaterialBuffer.hlsli"
#include "AnimationBuffer.hlsli"
#include "MeshBuffer.hlsli"
#include "VertexShaderOutputType.hlsli"

VertexOutput_PCNT_P VS(Vertex_PCNTs input)
{
	float4 pos = mul(input.Position, WorldTransformMatrix);
	pos = mul(pos, ViewMatrix);
	pos = mul(pos, ProjectionMatrix);

	VertexOutput_PCNT_P output = (VertexOutput_PCNT_P)0;
	output.p = pos;
	output.c = input.Color;
	output.n = input.Normal;
	output.t = input.Diffuse;
	//output.param.x = input.MaterialIndex;
	output.Index = input.MaterialIndex;

	return output;
}
