// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Camera : register(b0)
{
	matrix CameraPosition : packoffset(c0);
	matrix ViewMatrix : packoffset(c4);
	matrix ProjectionMatrix : packoffset(c8);
};
