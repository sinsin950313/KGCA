#pragma once

#include "Common.h"
#include "Mesh.h"
#include "Animation.h"
#include "Material.h"
#include <map>
#include "Shader.h"
#include "VolumeType.h"

namespace SSB
{
	//typedef std::string AnimationName;
	//extern const AnimationName kDefaultAnimaionName;

	class Model : public Common
	{
	//private:
	//	static Animation DefaultAnimation;

	private:
		std::vector<Vector3> _meshElementMinMaxVertexList;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		std::map<MaterialIndex, Material*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;

		//std::map<AnimationName, Animation*> _animations;
		//Animation* _currentAnimation;

		VertexShader* _vs;
		PixelShader* _ps;

	public:
		Model();
		virtual ~Model();

	private:
		void SizeCheck();

	public:
		void RegisterMesh(MeshIndex index, MeshInterface* mesh);
		void RegisterMaterial(MaterialIndex index, Material* material);
		//void RegisterAnimation(AnimationName name, Animation* animation);
		//void SetCurrentAnimation(AnimationName name);
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
}
