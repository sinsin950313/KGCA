#include "LightBufferData.hlsli"

float4 ComputeDiffuseLight(VertexData vertexData, LightData lightData, float attenuation)
{
	float4 lightDirection = normalize(vertexData.Position - lightData.Position);
	float intensity = saturate(dot(vertexData.Normal, -lightDirection));
	return lightData.Color * intensity * attenuation;
}

float4 ComputeSpecularLight(VertexData vertexData, LightData lightData, float4 eyeDirection, float attenuation, float specularFactor)
{
	float4 reflectionVector = reflect(lightData.Direction, vertexData.Normal);
	float intensity = pow(saturate(dot(-eyeDirection, reflectionVector)), specularFactor);
	return lightData.Color * intensity * attenuation;
}

float GetAttenuation(VertexData vertexData, LightData lightData)
{
	float dist = distance(vertexData.Position, lightData.Position);
	return 1.0f / (1 + pow(distance, 2));
}

float4 ComputeDirectionalLight(VertexData vertexData, LightData lightData, LightComputationParam param)
{
	float4 diffuse = ComputeDiffuseLight(vertexData, lightData, 1);
	float4 SpecularLight = ComputeSpecularLight(vertexData, lightData, eyeDirection, 1, param.SpecularFactor);
}

float4 ComputePointLight(VertexData vertexData, LightData lightData, LightComputationParam param)
{
	float attenuation = GetAttenuation(vertexData, lightData);
	float4 diffuse = ComputeDiffuseLight(vertexData, lightData, attenuation);
	float4 SpecularLight = ComputeSpecularLight(vertexData, lightData, eyeDirection, attenuation, param.SpecularFactor);
}

float4 ComputeSpotLight(VertexData vertexData, LightData lightData, LightComputationParam param)
{
	float attenuation = GetAttenuation(vertexData, lightData);
	float4 diffuse = ComputeDiffuseLight(vertexData, lightData, attenuation);
	float4 SpecularLight = ComputeSpecularLight(vertexData, lightData, eyeDirection, attenuation, param.SpecularFactor);
}
