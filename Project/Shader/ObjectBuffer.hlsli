// Camera : Register 0
// Object : Register 1
// Material : Register 2
// Animation : Register 3
// Mesh : Register 4

cbuffer Object : register(b1)
{
	matrix World : packetoffset(c0);
};
