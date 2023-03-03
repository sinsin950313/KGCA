// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Animation : register(b3)
{
	matrix BoneAnimationMatrix[255];
	matrix MeshAnimationMatrix[255];
};
