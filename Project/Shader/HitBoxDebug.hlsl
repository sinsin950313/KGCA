Texture2D g_txTextureA : register(t0);
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

float4 Main(PS_input input) : SV_TARGET
{
	//return float4(1, 0, 0, 1);
	float4 vColor = g_txTextureA.Sample(g_sampleA, input.t);
	if(vColor.r < 50/255.0f && vColor.g < 50/255.0f && vColor.b < 60/255.0f)
	{
		discard;
	}
	vColor.r = vColor.r + 0.4f;
	vColor.b = vColor.b - 0.2f;
	return vColor;
}

float4 Debug(PS_input input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}
