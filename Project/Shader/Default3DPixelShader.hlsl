Texture2D g_txTextureA : register(t0);
Texture2D g_txTexMaskA : register(t1);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 Main(PS_input input) : SV_TARGET
{
	return g_txTextureA.Sample(g_sampleA, input.t);
	//return input.n;
}
