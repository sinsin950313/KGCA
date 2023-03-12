#pragma once

#include "Common.h"
#include "Mesh.h"
#include "Animation.h"
#include "Material.h"
#include <map>
#include "Shader.h"
#include "VolumeType.h"
#include "Serializeable.h"
#include "Animation.h"
#include "EditableInterface.h"

namespace SSB
{
	typedef std::string AnimationName;

	class Model : public Common, public Serializeable, public EditableInterface<Model>
	{
	private:
		static Animation DefaultAnimation;

	private:
		std::vector<Vector3> _meshElementMinMaxVertexList;
		Vector3 _minVertex;
		Vector3 _maxVertex;

		std::map<MaterialIndex, Material*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;

		std::map<AnimationName, Animation*> _animations;
		Animation* _currentAnimation;

		PixelShader* _ps;

		// Serialize or make Skeleton
		std::map<SocketName, BoneIndex> _sockets;

	public:
		Model();
		virtual ~Model();

	private:
		void SizeCheck();

	public:
		void Initialize_RegisterMaterial(MaterialIndex index, Material* material);
		void Initialize_RegisterMesh(MeshIndex index, MeshInterface* mesh);
		void Initialize_RegisterAnimation(AnimationName name, Animation* animation);
		void Initialize_RegisterSocket(SocketName name, BoneIndex index);

	public:
		void SetCurrentAnimation(AnimationName name);
		void SetVertexShader(VertexShader* shader);
		void SetPixelShader(PixelShader* shader);
		HMatrix44 GetSocketCurrentLocation(SocketName name);

	public:
		operator OBBData();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		std::string Serialize(int tabCount) override;
		void Deserialize(std::string& serialedString) override;
		EditableObject<Model>* GetEditableObject() override;
	};

	class EditableModelObject : public EditableObject<Model>
	{
	private:
		std::map<MaterialIndex, Material*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;
		std::map<AnimationName, Animation*> _animations;

		PixelShader* _ps;

	public:
		EditableModelObject(std::map<MaterialIndex, Material*> materials, std::map<MeshIndex, MeshInterface*> meshes, std::map<AnimationName, Animation*> animations, PixelShader* ps);

	public:
		std::map<MaterialIndex, Material*> GetMaterials();
		std::map<MeshIndex, MeshInterface*> GetMeshes();
		std::map<AnimationName, Animation*> GetAnimations();
		PixelShader* GetPixelShader();

	public:
		void RemoveAction(AnimationName actionName);
		void AddAction(AnimationName actionName, Animation* animation);

	public:
		Model* GetResult() override;
	};
}
