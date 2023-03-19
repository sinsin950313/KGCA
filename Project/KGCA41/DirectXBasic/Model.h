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

		// Serialize
		std::map<SocketName, BoneIndex> _sockets;

		// Temp for Team Project
		OBBData _boundingVolume;

		Skeleton* _skeleton = nullptr;

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
		void Initialize_SetBoundingVolume(OBBData data);
		void Initialize_SetSkeleton(Skeleton* skeleton);

	public:
		void SetCurrentAnimation(AnimationName name);
		void SetVertexShader(VertexShader* shader);
		void SetPixelShader(PixelShader* shader);
		HMatrix44 GetSocketCurrentMatrix(SocketName name);
		OBBData GetBoundingVolume();

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

	struct EditableModelData
	{
		std::map<MeshIndex, MeshInterface*> Meshes;
		std::map<SocketName, BoneIndex> Sockets;
		std::string PixelShaderFileName;
		OBBData BoundingVolume;

		std::map<MaterialIndex, Material*> Materials;
		std::map<AnimationName, Animation*> Animations;
	};
	class EditableModelObject : public EditableObject<Model>
	{
	private:
		std::map<MeshIndex, MeshInterface*> _meshes;
		std::map<SocketName, BoneIndex> _sockets;
		std::string _pixelShaderFileName;
		OBBData _boundingVolume;

		std::map<MaterialIndex, Material*> _materials;
		std::map<AnimationName, Animation*> _animations;

	public:
		EditableModelObject(EditableModelData data);

	public:
		std::map<SocketName, BoneIndex> GetSockets();
		std::string GetPixelShaderFileName();
		OBBData GetBoundingVolumeData();
		std::map<MeshIndex, MeshInterface*> GetMeshes();

		std::map<MaterialIndex, Material*> GetMaterials();
		std::map<AnimationName, Animation*> GetAnimations();

	public:
		void ResizeBoundingVolume(OBBData data);
		void ChangePixelShaderFile(std::string fileName);

	public:
		Model* GetResult() override;
	};
}
