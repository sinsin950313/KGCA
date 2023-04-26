Texture2D Diffuse : register(t0);
Texture2D DiffuseArray[16] : register(t0);

Texture2D DiffuseMask : register(t1);
Texture2D DiffuseMaskArray[16] : register(t1);

SamplerState Sampler : register(s0);

struct PixelShaderInput_PC
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR0;
};

struct PixelShaderInput_PCNT
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR0;
	float4 Normal : NORMAL;
	float2 Diffuse : TEXCOORD0;
};

struct PixelShaderInput_PCNT_P
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR0;
	float4 Normal : NORMAL;
	float2 Diffuse : TEXCOORD0;
	//float4 Parameter : TEXCOORD1;
	uint Index : SV_RenderTargetArrayIndex;
};

float4 GetDiffuseColor(uint index, float2 uv)
{
	float4 fColor = float4(1, 1, 1, 1);
	switch (index)
	{
	case 0: fColor = DiffuseArray[0].Sample(Sampler, uv); break;
	case 1: fColor = DiffuseArray[1].Sample(Sampler, uv); break;
	case 2: fColor = DiffuseArray[2].Sample(Sampler, uv); break;
	case 3: fColor = DiffuseArray[3].Sample(Sampler, uv); break;
	case 4: fColor = DiffuseArray[4].Sample(Sampler, uv); break;
	case 5: fColor = DiffuseArray[5].Sample(Sampler, uv); break;
	case 6: fColor = DiffuseArray[6].Sample(Sampler, uv); break;
	case 7: fColor = DiffuseArray[7].Sample(Sampler, uv); break;
	case 8: fColor = DiffuseArray[8].Sample(Sampler, uv); break;
	case 9: fColor = DiffuseArray[9].Sample(Sampler, uv); break;
	case 10: fColor = DiffuseArray[10].Sample(Sampler, uv); break;
	case 11: fColor = DiffuseArray[11].Sample(Sampler, uv); break;
	case 12: fColor = DiffuseArray[12].Sample(Sampler, uv); break;
	case 13: fColor = DiffuseArray[13].Sample(Sampler, uv); break;
	case 14: fColor = DiffuseArray[14].Sample(Sampler, uv); break;
	case 15: fColor = DiffuseArray[15].Sample(Sampler, uv); break;	
	}
	return fColor;
}
