struct VS_in
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float4 Texture : Texture;
};

cbuffer ViewSpaceTransform : register(b0)
{
	matrix Position : packoffset(c0);
	matrix View : packoffset(c4);
	matrix Projection : packoffset(c8);
};

cbuffer ObjectToWorldTransform : register(b1)
{
	matrix World : packoffset(c0);
}

struct VS_out
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_out VSMain(VS_in input)
{
	float4 world = mul(input.Position, World);
	float4 view = mul(world, View);
	float4 proj = mul(view, Projection);

	VS_out output = (VS_out)0;
	output.p = proj;
	output.n = input.Normal;
	output.c = input.Color;
	output.t = input.Texture;

	return output;
}

struct PS_in
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 PSMain(PS_in input) : SV_TARGET
{
	return input.c;
}