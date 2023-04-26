struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float4 n : NORMAL;
	float2 t : TEXCOORD0;
};

float4 PS(PS_input input) : SV_TARGET
{
	return input.c;
	//return g_txTextureA.Sample(g_sampleA, input.t) * input.c;
	//return input.n;
}
