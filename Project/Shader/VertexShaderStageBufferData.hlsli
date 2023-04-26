struct VS_in
{
	float4 p : Position;
	float4 c : Color;
	float4 n : Normal;
	float2 t : Texture;

	int4 AffectingBoneIndex : AffectingBoneIndex;
	float4 Weight : Weight;
};

cbuffer ViewSpaceTransform : register(b0)
{
	matrix Position : packoffset(c0);
	matrix View : packoffset(c4);
	matrix Projection : packoffset(c8);
};

cbuffer ObjectToWorldTransform : register(b1)
{
	matrix World : packoffset(c0);
}

cbuffer AnimatedTransform : register(b2)
{
	matrix AnimatedMeshMatrix[255];
	matrix AnimatedBoneMatrix[255];
}

cbuffer MeshData : register(b3)
{
	matrix BoneSpaceTransform[255] : BoneSpaceTransform;
	int MeshIndex;
	int padding[3];
}

struct VS_out
{
	float4 p : SV_POSITION;
	float4 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

