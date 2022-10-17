struct VS_in
{
	float2 p : Position;
	float4 c: Color;
	float2 t: Texture;
};

struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_out Main(VS_in input)
{
	VS_out output = (VS_out)0;

	output.p = float4(input.p, 0.0f, 1.0f);
	output.c = input.c;
	output.t = input.t;

	return output;
}
