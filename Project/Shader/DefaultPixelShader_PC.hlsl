#include "PixelShaderInputType.hlsli"

float4 PS(PixelShaderInput_PC input) : SV_TARGET
{
	return input.Color;
}
