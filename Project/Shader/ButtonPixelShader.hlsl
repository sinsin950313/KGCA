Texture2D g_txTextureA : register(t0);
SamplerState g_sampleA : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 Main(PS_input input) : SV_TARGET
{
	float4 vColor = g_txTextureA.Sample(g_sampleA, input.t);
	if(vColor.r < 0.01f && vColor.g < 0.01f && vColor.b < 0.01f)
	{
		discard;
	}

	// vColor.r = 1;
	// vColor.g = 1;
	// vColor.b = 0;

	return vColor;
}
