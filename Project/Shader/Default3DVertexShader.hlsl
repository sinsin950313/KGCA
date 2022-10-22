struct VS_in
{
	float4 p : Position;
	float4 c : Color;
	float2 t : Texture;
};

struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

cbuffer ConstantData : register(b0)
{
	matrix g_World : packoffset(c0);
	matrix g_View : packoffset(c4);
	matrix g_Projection : packoffset(c8);
};

VS_out Main(VS_in input)
{
	VS_out output = (VS_out)0;

	float4 local = input.p;
	float4 world = mul(local, g_World);
	float4 view = mul(world, g_View);
	float4 proj = mul(view, g_Projection);

	output.p = proj;
	output.c = input.c;
	output.t = input.t;

	return output;
}
