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

VS_out main(VS_in input)
{
	VS_out output = (VS_out)0;

	output.p = input.p;
	output.p.w = 1.0f;
	output.c = input.c;
	output.t = input.t;

	return output;
}