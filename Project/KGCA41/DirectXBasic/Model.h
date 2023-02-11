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

	struct MeshData
	{
		HMatrix44 TransformBuffer[255];
		int MeshIndex = 0;
		int padding[3];
	};

	struct SkinningVertexData
	{
		Vertex_PNCT Vertex;
		int AffectedBoneIndex[4];
		float Weight[4];
	};

	typedef int MeshIndex;

	class Mesh : public Common
	{
	private:
		std::vector<Vertex_PNCT> _vertexList;
		ID3D11Buffer* _vertexBuffer;
		std::vector<DWORD> _indexList;
		ID3D11Buffer* _indexBuffer;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		MeshData _meshData;
		ID3D11Buffer* _meshDataBuffer;

		std::vector<SkinningVertexData> _skinningData;
		ID3D11Buffer* _skinningDataBuffer;

	private:
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		bool CreateSkinningDataBuffer();
		bool CreateBoneSpaceTransformBuffer();

	public:
		void SetVertexList(std::vector<Vertex_PNCT> vertexList);
		void SetIndexList(std::vector<DWORD> indexList);

	public:
		Vector3 GetMinVertex();
		Vector3 GetMaxVertex();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	const int kAnimationUnitMaxIndex = 255;
	struct AnimationUnitInfo
	{
		HMatrix44 Matrix;
		Vector3 Translate;
		Vector3 Scale{ 1, 1, 1 };
		Quaternion Rotate;
	};
	struct AnimationFrameInfo
	{
		AnimationUnitInfo MeshUnit[kAnimationUnitMaxIndex];
		AnimationUnitInfo BoneUnit[kAnimationUnitMaxIndex];
	};

	class Animation : public Common
	{
	private:
		struct AnimatedFrameInfo
		{
			HMatrix44 MeshUnit[kAnimationUnitMaxIndex];
			HMatrix44 BoneUnit[kAnimationUnitMaxIndex];
		};

	private:
		const AnimatedFrameInfo DefaultFrameInfo;

	private:
		float _framePerSecond = 30;
		Timer _animationTimer;

		int _boneMaxIndex = 0;
		int _meshMaxIndex = 0;
		std::vector<AnimationFrameInfo> _data;

		AnimatedFrameInfo _currentFrameInfo;
		ID3D11Buffer* _animatedFrameBuffer;

	public:
		Animation();
		~Animation();

	private:
		bool CreateAnimatedFrameInfoBuffer();
		HMatrix44 GetInterpolate(AnimationUnitInfo& beforeInfo, AnimationUnitInfo& afterInfo, float t);
		void UpdateFrameInfo();

	public:
		void SetAnimationFrameData(std::vector<AnimationFrameInfo> data);
		void SetMeshMaxIndex(int maxIndex);
		void SetBoneMaxIndex(int maxIndex);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	typedef std::string AnimationName;
	extern const AnimationName kDefaultAnimaionName;

	class Model : public Common
	{
	private:
		static Animation DefaultAnimation;

	private:
		ID3D11InputLayout* _vertexLayout;
		Shader* _vs;
		Shader* _ps;
		std::vector<Vector3> _meshElementMinMaxVertexList;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		std::map<MeshIndex, Mesh*> _meshes;

		std::map<AnimationName, Animation*> _animations;
		Animation* _currentAnimation;

	protected:
		//std::vector<Sprite*> _sprites;
		Sprite* _sprite;

	public:
		Model();
		virtual ~Model();

	private:
		void SizeCheck();
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count);

	private:
		bool CreateVertexLayout();

	public:
		//std::vector<Vertex_PNCT>& GetVertexList() { return _vertexList; }
		//std::vector<DWORD>& GetIndexList() { return _indexList; }
		void SetSprite(Sprite* sprite);
		//Sprite* GetSprite() { return _sprite; }
		void RegisterMesh(MeshIndex index, Mesh* mesh);
		void RegisterAnimation(AnimationName name, Animation* animation);
		void SetCurrentAnimation(AnimationName name);
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

	//class Direction : public Model
	//{
	//private:
	//	void Build() override;
	//};

	//class Triangle : public Model
	//{
	//private:

	//private:
	//	void Build() override;
	//};

	//class Box : public Model
	//{
	//private:
	//	float _width;
	//	float _height;
	//	float _depth;

	//public:
	//	Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	//private:
	//	void Build() override;
	//};
}
