struct VertexData
{
	float4 Position;
	float4 Normal;
	float4 Color;
	float2 Texture;
};

cbuffer AmbientLightData : register(b15)
{
	float3 LightAmbientCoefficient;
}

cbuffer LightData : register(b14)
{
	float3 LightPosition;
	float LightPadding1;
	float3 LightDirection;
	float LightPadding2;
	float3 LightColor;
	float LightPadding3;
};

cbuffer DirectionalLightData : register(b13)
{
};

cbuffer PointLightData : register(b12)
{
	float LightRadius;
}

cbuffer SpotLightData : register(b11)
{
	float LightInCornRadius;
	float LightOutCornRadius;
}

struct LightData
{
	float4 Position;
	float4 Direction;
	float4 Color;
}

struct LightComputationParam
{
	float4 EyeDirection;
	float SpecularFactor;
	float3 Padding;
}
