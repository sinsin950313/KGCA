struct VS_IN
{
	float4 p : Position;
	float4 c : Color;
	float2 t : Texture;
};

struct VS_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

cbuffer ConstantBuffer : register(b0)
{
	matrix world : packoffset(c0);
	matrix view : packoffset(c4);
	matrix projection : packoffset(c8);
};

VS_OUT Main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;
	float4 vertexLocal = input.p;
	float4 vertexWorld = mul(vertexLocal, world);
	float4 vertexView = mul(vertexWorld, view);
	float4 vertexProj = mul(vertexView, projection);
	output.p = vertexProj;
	output.c = input.c;
	output.t = input.t;

	return output;
}
