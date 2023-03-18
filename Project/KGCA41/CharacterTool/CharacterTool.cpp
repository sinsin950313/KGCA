#define _CRT_SECURE_NO_WARNINGS

#include "CharacterTool.h"
#include <string>
#include "CommonPath.h"
#include "ShaderManager.h"
#include "CommonUtility.h"
#include "Common.h"
#include "Animation.h"
#include "EditableInterface.h"
#include "FileIOObject.h"

namespace SSB
{
	void CharacterTool::Import()
	{
		Init();

		if (!_objectFileName.empty())
		{
			FBXLoader loader;
			loader.Init();
			loader.SetFileName(_objectFileName);
			{
				auto loadedMaterials = loader.LoadMaterial();
				if (!loadedMaterials.empty())
				{
					for (auto material : loadedMaterials)
					{
						EditableMaterialObject* object = static_cast<EditableMaterialObject*>(material.second->GetEditableObject());
						_materials.insert(std::make_pair(material.first, object));
					}
				}
			}

			{
				Model* model = loader.LoadModel();

				EditableModelObject* editableObject = static_cast<EditableModelObject*>(model->GetEditableObject());
				auto meshes = editableObject->GetMeshes();
				_meshes.clear();
				for (auto mesh : meshes)
				{
					_meshes.insert(std::make_pair(mesh.first, mesh.second->Clone()));
				}
				_pixelShaderFileName = editableObject->GetPixelShaderFileName();
				delete editableObject;
			}

			{
				auto animations = loader.LoadAnimation();
				for (auto animation : animations)
				{
					EditableAnimationObject* object = static_cast<EditableAnimationObject*>(animation.second->GetEditableObject());
					_animations.insert(std::make_pair(animation.first, object));
				}
			}

			{
				_skeleton = static_cast<EditableSkeletonObject*>(loader.LoadSkeleton()->GetEditableObject());
			}

			_objectFileName.clear();
		}
		else if (!_scriptFileName.empty())
		{
			ObjectScriptIO io;
			auto str = io.Read(_scriptFileName);
			Model model;
			model.Deserialize(str);

			EditableModelObject* editableObject = static_cast<EditableModelObject*>(model.GetEditableObject());
			{
				_materials.clear();

				auto materials = editableObject->GetMaterials();
				for (auto material : materials)
				{
					EditableMaterialObject* object = static_cast<EditableMaterialObject*>(material.second->GetEditableObject());
					_materials.insert(std::make_pair(material.first, object));
				}
			}
			{
				_meshes.clear();

				auto meshes = editableObject->GetMeshes();
				for (auto mesh : meshes)
				{
					_meshes.insert(std::make_pair(mesh.first, mesh.second));
				}
			}
			{
				auto animations = editableObject->GetAnimations();
				for (auto animation : animations)
				{
					EditableAnimationObject* object = static_cast<EditableAnimationObject*>(animation.second->GetEditableObject());
					_animations.insert(std::make_pair(animation.first, object));
				}
			}
			_pixelShaderFileName = editableObject->GetPixelShaderFileName();
			delete editableObject;

			{
				// Import Skeleton Data from File Name
			}

			_scriptFileName.clear();
		}
	}
	void CharacterTool::Export()
	{
		if (_scriptFileName.empty())
		{
			_scriptFileName = "NewFBXScriptFile";
		}
		{
			auto ret = SplitPath(mtw(_scriptFileName));
			if (ret[3].empty() || ret[3] != L".Script")
			{
				_scriptFileName = wtm(ret[2]) + ".Script";
			}
		}

		Model tmp;

		for (auto material : _materials)
		{
			tmp.Initialize_RegisterMaterial(material.first, material.second->GetResult());
		}

		for (auto mesh : _meshes)
		{
			tmp.Initialize_RegisterMesh(mesh.first, mesh.second->Clone());
		}

		for (auto animation : _animations)
		{
			tmp.Initialize_RegisterAnimation(animation.first, animation.second->GetResult());
		}

		{
			// Export Skeleton File Name
		}

		tmp.Init();
		tmp.SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(mtw(_pixelShaderFileName), "PS", "ps_5_0"));
		auto serialedStr = tmp.Serialize(0);

		ObjectScriptIO ioObject;
		ioObject.Write(_scriptFileName, serialedStr);
	}
	void CharacterTool::RegisterObjectFileName(std::string fileName)
	{
		_objectFileName = fileName;
	}
	void CharacterTool::ClearAnimationSelection()
	{
		{
			_selectedAnimation.AnimationName.clear();
			_selectedAnimation.EndFrame = kEmptyFrame;
		}
	}
	void CharacterTool::RegisterScriptFileName(std::string fileName)
	{
		_scriptFileName = fileName;
	}
	bool CharacterTool::IsSelected()
	{
		return !_selectedAnimation.AnimationName.empty();
	}
	void CharacterTool::AddAction(std::string actionFileName)
	{
		FBXLoader loader;
		loader.Init();
		loader.SetFileName(actionFileName);

		std::map<AnimationName, Animation*> anim = loader.LoadAnimation();
		for (auto iter : anim)
		{
			EditableAnimationObject* object = static_cast<EditableAnimationObject*>(iter.second->GetEditableObject());
			for (auto socket : _sockets)
			{
				object->AddSocketAnimation(socket.second.Index, socket.second.ParentIndex, socket.second.LocalMatrix);
			}
			_animations.insert(std::make_pair(iter.first, object));
		}
	}
	void CharacterTool::RemoveAction(std::string actionName)
	{
		_animations.erase(actionName);
		ClearAnimationSelection();
	}
	void CharacterTool::SelectCurrentAction(std::string actionName)
	{
		ClearAnimationSelection();

		if (_animations.find(actionName) != _animations.end())
		{
			_selectedAnimation.AnimationName = actionName;
			_selectedAnimation.EndFrame = _animations.find(actionName)->second->GetEndFrame();
		}
	}
	void CharacterTool::CutSelectedAnimataion(std::string newActionName, unsigned int lastFrame)
	{
		if (IsSelected())
		{
			EditableAnimationObject* editableObject = _animations.find(_selectedAnimation.AnimationName)->second;
			_animations.erase(_selectedAnimation.AnimationName);

			FrameIndex currentEndFrame = editableObject->GetEndFrame();

			{
				editableObject->EditFrame(0, lastFrame);
				Animation* before = editableObject->GetResult();
				AnimationName beforeName = newActionName;
				EditableAnimationObject* object = static_cast<EditableAnimationObject*>(before->GetEditableObject());
				_animations.insert(std::make_pair(beforeName, object));
			}

			{
				editableObject->EditFrame(lastFrame, currentEndFrame);
				Animation* after = editableObject->GetResult();
				AnimationName afterName = _selectedAnimation.AnimationName;
				EditableAnimationObject* object = static_cast<EditableAnimationObject*>(after->GetEditableObject());
				_animations.insert(std::make_pair(afterName, object));
			}
		}
	}
	void CharacterTool::ChangeSelectedAnimationData(std::string actionName, unsigned int frameSize)
	{
		if (IsSelected())
		{
			if (!actionName.empty())
			{
				EditableAnimationObject* object = _animations.find(_selectedAnimation.AnimationName)->second;
				_animations.erase(_selectedAnimation.AnimationName);
				_animations.insert(std::make_pair(actionName, object));

				SelectCurrentAction(actionName);
			}

			if (frameSize != kEmptyFrame)
			{
				_animations.erase(_selectedAnimation.AnimationName);

				EditableAnimationObject* editableObject = _animations.find(_selectedAnimation.AnimationName)->second;
				editableObject->EditFrame(0, frameSize);
			}

			SelectCurrentAction(actionName);
		}
	}
	void CharacterTool::AddSocket(SocketName socketName, BoneIndex parentIndex, HMatrix44 localMatrix)
	{
		BoneInfo boneInfo;
		boneInfo.Name = socketName;
		boneInfo.ParentIndex = parentIndex;
		boneInfo.LocalMatrix = localMatrix;

		BoneIndex index = _skeleton->AddSocket(boneInfo);
		for (auto animation : _animations)
		{
			animation.second->AddSocketAnimation(index, parentIndex, localMatrix);
		}

		SocketInfo socketInfo;
		socketInfo.Index = index;
		socketInfo.ParentIndex = parentIndex;
		socketInfo.LocalMatrix = localMatrix;
		_sockets.insert(std::make_pair(socketName, socketInfo));
	}
	std::map<MaterialIndex, Material*> CharacterTool::GetMaterials()
	{
		std::map<MaterialIndex, Material*> ret;
		for (auto material : _materials)
		{
			ret.insert(std::make_pair(material.first, material.second->GetResult()));
		}
		return ret;
	}
	std::map<MeshIndex, MeshInterface*> CharacterTool::GetMeshes()
	{
		std::map<MeshIndex, MeshInterface*> ret;
		for (auto mesh : _meshes)
		{
			ret.insert(std::make_pair(mesh.first, mesh.second->Clone()));
		}
		return ret;
	}
	std::map<AnimationName, Animation*> CharacterTool::GetActions()
	{
		std::map<AnimationName, Animation*> ret;
		for (auto animation : _animations)
		{
			ret.insert(std::make_pair(animation.first, animation.second->GetResult()));
		}
		return ret;
	}
	Skeleton* CharacterTool::GetSkeleton()
	{
		return _skeleton->GetResult();
	}
	PixelShader* CharacterTool::GetPixelShader()
	{
		return ShaderManager::GetInstance().LoadPixelShader(mtw(_pixelShaderFileName), "PS", "ps_5_0");
	}
	std::vector<ActionData> CharacterTool::GetActionList()
	{
		std::vector<ActionData> ret;
		for (auto action : _animations)
		{
			ActionData data;
			data.AnimationName = action.first;
			data.EndFrame = action.second->GetEndFrame();
			ret.push_back(data);
		}
		return ret;
	}
	DXObject* CharacterTool::GetPreviewObject()
	{
		DXObject* ret = new DXObject;
		ret->Init();

		Model* model = new Model;
		for (auto material : _materials)
		{
			Material* copy = material.second->GetResult();
			copy->Init();
			model->Initialize_RegisterMaterial(material.first, copy);
		}

		for (auto mesh : _meshes)
		{
			MeshInterface* copy = mesh.second->Clone();
			copy->Init();
			model->Initialize_RegisterMesh(mesh.first, copy);
		}

		for (auto animation : _animations)
		{
			Animation* copy = animation.second->GetResult();
			copy->Init();
			model->Initialize_RegisterAnimation(animation.first, copy);
		}

		for (auto socket : _sockets)
		{
			model->Initialize_RegisterSocket(socket.first, socket.second.Index);
		}

		model->Init();

		model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(mtw(_pixelShaderFileName), "PS", "ps_5_0"));
		ret->SetModel(model);
		if (IsSelected())
		{
			model->SetCurrentAnimation(_selectedAnimation.AnimationName);
		}

		return ret;
	}
	bool CharacterTool::Init()
	{
		for (auto material : _materials)
		{
			delete material.second;
		}
		_materials.clear();

		for (auto mesh : _meshes)
		{
			mesh.second->Release();
			delete mesh.second;
		}
		_meshes.clear();

		ClearAnimationSelection();

		for (auto animation : _animations)
		{
			delete animation.second;
		}
		_animations.clear();

		//_objectFileName.clear();
		//_scriptFileName.clear();

		return false;
	}
	bool CharacterTool::Frame()
	{
		return false;
	}

	bool CharacterTool::Release()
	{
		return true;
	}

	bool CharacterTool::Render()
	{
		return true;
	}
}
