// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Animation : register(c3)
{
	matrix BoneMatrix[255];
	matrix MeshMatrix[255];
};
