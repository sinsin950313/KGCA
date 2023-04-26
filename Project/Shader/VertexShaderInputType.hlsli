struct Vertex_PC
{
	float4 Position : Position;
	float4 Color : Color;
};

struct Vertex_PCNT
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float2 Diffuse : Diffuse;
};

struct Vertex_PCNT_Skinning
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float2 Diffuse : Diffuse;
	int4 BoneIndex : AffectingBoneIndex;
	float4 Weight : Weight;
};

struct Vertex_PCNTs
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float2 Diffuse : Diffuse;
	uint MaterialIndex : MaterialIndex;
};

struct Vertex_PCNTs_Skinning
{
	float4 Position : Position;
	float4 Color : Color;
	float4 Normal : Normal;
	float2 Diffuse : Diffuse;
	int4 BoneIndex : AffectingBoneIndex;
	float4 Weight : Weight;
	uint MaterialIndex : MaterialIndex;
};

