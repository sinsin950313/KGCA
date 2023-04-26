struct VertexOutput_PC
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};

struct VertexOutput_PCNT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float4 n : Normal;
	float2 t : TEXCOORD0;
};

struct VertexOutput_PCNT_P
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float4 n : Normal;
	float2 t : TEXCOORD0;
	//float4 param : TEXCOORD1;
	uint Index : SV_RenderTargetArrayIndex;
};

