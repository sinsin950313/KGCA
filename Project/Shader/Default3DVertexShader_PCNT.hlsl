struct VS_in
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float2 Texture : Texture;
};

cbuffer Camera : register(b0)
{
	matrix g_World : packoffset(c0);
	matrix g_View : packoffset(c4);
	matrix g_Projection : packoffset(c8);
};

struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float4 n : Normal;
	float2 t : TEXCOORD0;
};

VS_out VS(VS_in input)
{
	float4 pos = mul(input.Position, g_World);
	pos = mul(pos, g_View);
	pos = mul(pos, g_Projection);

	VS_out output = (VS_out)0;
	output.p = pos;
	output.c = input.Color;
	output.n = input.Normal;
	output.t = input.Texture;

	return output;
}

