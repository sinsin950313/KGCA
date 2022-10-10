struct VS_in
{
	float3 p : Position;
	float4 c : Color;
};
struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};

VS_out main(VS_in input)
{
	VS_out output = (VS_out)0;
	output.p = float4(input.p, 1.0f);
	output.c = input.c;
	return output;
}