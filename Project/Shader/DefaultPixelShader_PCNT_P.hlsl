#include "PixelShaderInputType.hlsli"

float4 PS(PixelShaderInput_PCNT_P input) : SV_TARGET
{
	return GetDiffuseColor(input.Parameter[0], input.Diffuse);
}
