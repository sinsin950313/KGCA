// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Mesh_Animatable : register(b4)
{
	int MeshIndex;
};

cbuffer Mesh_Skinning : register(b4)
{
	matrix ToBoneSpaceTransformMatrix[255];
};

