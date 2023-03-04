#include "PixelShaderInputType.hlsli"

float4 PS(PixelShaderInput_PCNT_P input) : SV_TARGET
{
	return float4(GetDiffuseColor(input.Index, input.Diffuse).xyz, 1);
}
