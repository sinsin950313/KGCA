Texture2D g_txTextureA : register(t0);
Texture2D g_txTexMaskA : register(t1);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 withoutMask(PS_input input) : SV_TARGET
{
	//return input.c;

	return g_txTextureA.Sample(g_sampleA, input.t);
}

float4 main(PS_input input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}
