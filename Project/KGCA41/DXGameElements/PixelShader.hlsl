Texture2D g_txTextureA : register(t0);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 main(PS_input input) : SV_TARGET
{
	return g_txTextureA.Sample(g_sampleA, input.t);
	//return input.c;
}