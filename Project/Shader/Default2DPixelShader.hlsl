Texture2D g_txTextureA : register(t0);
Texture2D g_txTexMaskA : register(t1);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 WithoutMask(PS_input input) : SV_TARGET
{
	//return input.c;

	return g_txTextureA.Sample(g_sampleA, input.t);
}

float4 WithMask(PS_input input) : SV_TARGET
{
	//return input.c;

	//return g_txTextureA.Sample(g_sampleA, input.t);

	float4 vMask = g_txTexMaskA.Sample(g_sampleA, input.t);
	if(vMask.r > 0.5f)
	{
		discard;
	}
	float4 vColor = g_txTextureA.Sample(g_sampleA, input.t);
	return vColor;
}

float4 WireFrame(PS_input input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}
