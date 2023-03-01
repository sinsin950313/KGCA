// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Mesh_Animatable : register(c4)
{
	int MeshIndex;
};

cbuffer Mesh_PCNT_Skinning : register(c4)
{
	matrix ToBoneSpaceTransformMatrix[255];
};

