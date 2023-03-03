#include "PixelShaderInputType.hlsli"

float4 PS(PixelShaderInput_PCNT input) : SV_TARGET
{
	return Diffuse.Sample(Sampler, input.Diffuse);
}
