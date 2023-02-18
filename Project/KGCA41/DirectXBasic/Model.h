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
	struct Vertex_PNCT
	{
		Float4 position;
		Float4 normal;
		Float4 color;
		Float2 texture;
	};

	typedef int MeshIndex;

	struct MeshData
	{
		HMatrix44 BoneSpaceTransformBuffer[255];
		MeshIndex MeshIndex = 0;
		int padding[3];
	};

	static const int kAffectedBoneCount = 4;
	struct SkinningVertexData
	{
		int AffectedBoneIndex[kAffectedBoneCount];
		float Weight[kAffectedBoneCount];
	};

	class Mesh : public Common
	{
	private:
		ID3D11InputLayout* _vertexLayout;
		std::vector<Vertex_PNCT> _vertexList;
		ID3D11Buffer* _vertexBuffer;
		std::vector<DWORD> _indexList;
		ID3D11Buffer* _indexBuffer;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		std::vector<SkinningVertexData> _skinningDataPerVertex;
		ID3D11Buffer* _skinningDataBuffer;

		MeshData _meshData;
		ID3D11Buffer* _meshDataBuffer;

		VertexShader* _vs;
		PixelShader* _ps;

	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count);
		bool CreateVertexLayout();
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		bool CreateSkinningDataBuffer();
		bool CreateBoneSpaceTransformBuffer();

	public:
		void SetVertexList(std::vector<Vertex_PNCT> vertexList);
		void SetIndexList(std::vector<DWORD> indexList);
		void SetMeshData(MeshData data);
		void SetSkinninData(std::vector<SkinningVertexData> data);
		void SetVertexShader(VertexShader* shader);
		void SetPixelShader(PixelShader* shader);

	public:
		Vector3 GetMinVertex();
		Vector3 GetMaxVertex();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	static const int kAnimationUnitMaxIndex = 255;
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
		static const AnimationFrameInfo kDefaultFrameInfo;

	private:
		float _framePerSecond = 30;
		Timer _animationTimer;

		int _boneMaxCount = 0;
		int _meshMaxCount = 0;
		std::vector<AnimationFrameInfo> _data;

		AnimationFrameInfo _currentFrameInfo;
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
		void SetMaximumMeshCount(int count);
		void SetMaximumBoneCount(int count);

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

	public:
		//std::vector<Vertex_PNCT>& GetVertexList() { return _vertexList; }
		//std::vector<DWORD>& GetIndexList() { return _indexList; }
		void SetSprite(Sprite* sprite);
		//Sprite* GetSprite() { return _sprite; }
		void RegisterMesh(MeshIndex index, Mesh* mesh);
		void RegisterAnimation(AnimationName name, Animation* animation);
		void SetCurrentAnimation(AnimationName name);
		void SetVertexShader(VertexShader* shader);
		void SetPixelShader(PixelShader* shader);

	public:
		operator OBBData();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	//class Direction : public Mesh
	//{
	//public:
	//	Direction();
	//};

	class Triangle : public Mesh
	{
	public:
		Triangle();
	};

	class Box : public Mesh
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
	};
}
