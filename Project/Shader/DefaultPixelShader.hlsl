float4 Main(float4 p : SV_POSITION, float4 c : COLOR0) : SV_TARGET
{
	return c;
}

struct PS_input
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 FormedMain(PS_input input) : SV_TARGET
{
	return input.c;
	//return g_txTextureA.Sample(g_sampleA, input.t) * input.c;
	//return input.n;
}
