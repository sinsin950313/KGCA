#pragma once

#include "Common.h"
#include <vector>
#include "Vector.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Shader.h"
#include "Quaternion.h"
#include "VolumeType.h"

namespace SSB
{
	struct Vertex_PCT
	{
		Float4 position;
		Float4 color;
		Float2 texture;
	};

	struct Vertex_PNCT
	{
		Float4 position;
		Float4 normal;
		Float4 color;
		Float2 texture;
	};

	//class Animation : public Common
	//{
	//private:
	//	struct ActionFrameInfo
	//	{
	//		HMatrix44 Matrix;
	//		Vector3 Translate;
	//		Vector3 Scale;
	//		Quaternion Rotate;
	//	};
	//	struct ActionInfo
	//	{
	//		UINT EndFrame;
	//		std::vector<ActionFrameInfo> FrameInfoList;
	//	};

	//private:
	//	static ActionInfo DefaultAction;

	//private:
	//	float _tickPerFrame = 160;
	//	float _frameSpeed = 30;
	//	Timer _animationTimer;

	//	std::map<std::string, ActionInfo> _actionList;
	//	ActionInfo* _currentAction;
	//	int _currentFrame;

	//public:
	//	~Animation() { Release(); }

	//protected:
	//	HMatrix44 GetInterpolate();

	//public:
	//	void SetAdditionalAction(std::string name, ActionInfo info);
	//	void UpdateCurrentAction(std::string name);

	//public:
	//	bool Init() override;
	//	bool Frame() override;
	//	bool Render() override;
	//	bool Release() override;
	//};

	// Mass of mesh
	class Model : public Common
	{
	//protected:
	//	class Bone : public Common
	//	{
	//	public:
	//		bool Init() override;
	//		bool Frame() override;
	//		bool Render() override;
	//		bool Release() override;
	//	};

	private:
	//	Animation DefaultAnimation;

	private:
		ID3D11InputLayout* _vertexLayout;
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		Shader* _vs;
		Shader* _ps;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		//Animation* _animation;

	protected:
		std::vector<Vertex_PNCT> _vertexList;
		std::vector<DWORD> _indexList;
		//std::vector<Sprite*> _sprites;
		Sprite* _sprite;

	public:
		Model();
		virtual ~Model();

	private:
		void SizeCheck();
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count);

	private:
		virtual void Build() = 0;

	private:
		bool CreateVertexLayout();

	public:
		//std::vector<Vertex_PNCT>& GetVertexList() { return _vertexList; }
		//std::vector<DWORD>& GetIndexList() { return _indexList; }
		void SetSprite(Sprite* sprite);
		//Sprite* GetSprite() { return _sprite; }
		//void SetAnimation(Animation* animation);
		void UpdateCurrentAnimation(std::string name);
		void SetVertexShader(Shader* shader);
		void SetPixelShader(Shader* shader);

	public:
		operator OBBData();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class Direction : public Model
	{
	private:
		void Build() override;
	};

	class Triangle : public Model
	{
	private:

	private:
		void Build() override;
	};

	class Box : public Model
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	private:
		void Build() override;
	};
}
