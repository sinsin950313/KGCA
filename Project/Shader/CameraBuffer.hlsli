// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Camera : register(b0)
{
	matrix Position : packetoffset(c0);
	matrix View : packetoffset(c4);
	matrix Projection : packetoffset(c8);
};
