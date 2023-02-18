#pragma once

#include "Common.h"
#include <d3dcompiler.h>

class ID3D11DeviceChild;

namespace SSB
{
	class Shader : public Common
	{
	private:
		ID3D11DeviceChild* _shader;
		ID3DBlob* _code;

	protected:
		ID3D11DeviceChild* GetShader() { return _shader; }

	public:
		ID3DBlob* GetCode() { return _code; }

	public:
		Shader(ID3D11DeviceChild* shader, ID3DBlob* code);
		virtual ~Shader();

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader(ID3D11DeviceChild* shader, ID3DBlob* code);

	public:
		bool Render() override;
	};

	class PixelShader : public Shader
	{
	public:
		PixelShader(ID3D11DeviceChild* shader, ID3DBlob* code);

	public:
		bool Render() override;
	};
}
