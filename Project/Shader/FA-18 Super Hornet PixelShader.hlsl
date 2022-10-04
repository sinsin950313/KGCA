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
	if(vColor.g > 0.8f && vColor.r < 0.2f && vColor.b < 0.2f)
	{
		discard;
	}
	return vColor;
}

float4 WireFrame(PS_input input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}
