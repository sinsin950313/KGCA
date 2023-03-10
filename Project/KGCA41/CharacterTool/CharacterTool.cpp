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
			tmp.Initialize_RegisterMaterial(material.first, material.second->Clone());
		}

		for (auto mesh : _meshes)
		{
			tmp.Initialize_RegisterMesh(mesh.first, mesh.second->Clone());
		}

		for (auto animation : _animations)
		{
			tmp.Initialize_RegisterAnimation(animation.first, animation.second->Clone());
		}

		tmp.Init();
		tmp.SetPixelShader(_ps);
		auto serialedStr = tmp.Serialize(0);

		ObjectScriptIO ioObject;
		ioObject.Write(_scriptFileName, serialedStr);
	}
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
						_materials.insert(std::make_pair(material.first, material.second->Clone()));
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
				_ps = editableObject->GetPixelShader();
				delete editableObject;
			}

			{
				auto animations = loader.LoadAnimation();
				for (auto animation : animations)
				{
					_animations.insert(std::make_pair(animation.first, animation.second->Clone()));
				}
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
					_materials.insert(std::make_pair(material.first, material.second));
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
					_animations.insert(std::make_pair(animation.first, animation.second));
				}
			}
			_ps = editableObject->GetPixelShader();
			delete editableObject;

			_scriptFileName.clear();
		}
	}
	void CharacterTool::RegisterObjectFileName(std::string fileName)
	{
		_objectFileName = fileName;
	}
	void CharacterTool::ClearAnimationSelection()
	{
		{
			_selectedAnimation.AnimationPointer = nullptr;
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
		return _selectedAnimation.AnimationPointer != nullptr;
	}
	void CharacterTool::AddAction(std::string actionFileName)
	{
		FBXLoader loader;
		loader.Init();
		loader.SetFileName(actionFileName);

		std::map<AnimationName, Animation*> anim = loader.LoadAnimation();
		for (auto iter : anim)
		{
			_animations.insert(std::make_pair(iter.first, iter.second));
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
			_selectedAnimation.AnimationPointer = _animations.find(actionName)->second;
			_selectedAnimation.EndFrame = _selectedAnimation.AnimationPointer->GetFrameSize();
		}
	}
	void CharacterTool::CutSelectedAnimataion(std::string newActionName, unsigned int lastFrame)
	{
		if (IsSelected())
		{
			EditableAnimationObject* editableObject = static_cast<EditableAnimationObject*>(_selectedAnimation.AnimationPointer->GetEditableObject());
			_animations.erase(_selectedAnimation.AnimationName);
			delete _selectedAnimation.AnimationPointer;

			FrameIndex currentEndFrame = editableObject->GetEndFrame();

			{
				editableObject->EditFrame(0, lastFrame);
				Animation* before = editableObject->GetResult();
				AnimationName beforeName = newActionName;
				_animations.insert(std::make_pair(beforeName, before));
			}

			{
				editableObject->EditFrame(lastFrame, currentEndFrame);
				Animation* after = editableObject->GetResult();
				AnimationName afterName = _selectedAnimation.AnimationName;
				_animations.insert(std::make_pair(afterName, after));
			}
		}
	}
	void CharacterTool::ChangeSelectedAnimationData(std::string actionName, unsigned int frameSize)
	{
		if (IsSelected())
		{
			if (!actionName.empty())
			{
				_animations.erase(_selectedAnimation.AnimationName);
				_animations.insert(std::make_pair(actionName, _selectedAnimation.AnimationPointer));
				_selectedAnimation.AnimationName = actionName;
			}

			if (frameSize != kEmptyFrame)
			{
				_animations.erase(_selectedAnimation.AnimationName);

				EditableAnimationObject* editableObject = static_cast<EditableAnimationObject*>(_selectedAnimation.AnimationPointer->GetEditableObject());
				editableObject->EditFrame(0, frameSize);
				editableObject->GetResult();
				delete _selectedAnimation.AnimationPointer;

				Animation* result = editableObject->GetResult();
				_selectedAnimation.AnimationPointer = result;
				_animations.insert(std::make_pair(_selectedAnimation.AnimationName, _selectedAnimation.AnimationPointer));
			}

			_selectedAnimation.AnimationName = actionName;
			_selectedAnimation.EndFrame = frameSize;
		}
	}
	std::map<MaterialIndex, Material*> CharacterTool::GetMaterials()
	{
		std::map<MaterialIndex, Material*> ret;
		for (auto material : _materials)
		{
			ret.insert(std::make_pair(material.first, material.second->Clone()));
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
			ret.insert(std::make_pair(animation.first, animation.second->Clone()));
		}
		return ret;
	}
	PixelShader* CharacterTool::GetPixelShader()
	{
		return _ps;
	}
	std::vector<ActionData> CharacterTool::GetActionList()
	{
		std::vector<ActionData> ret;
		for (auto action : _animations)
		{
			ActionData data;
			data.AnimationName = action.first;
			data.EndFrame = action.second->GetFrameSize();
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
			Material* copy = material.second->Clone();
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
			Animation* copy = animation.second->Clone();
			copy->Init();
			model->Initialize_RegisterAnimation(animation.first, copy);
		}

		model->Init();

		model->SetPixelShader(_ps);
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
			material.second->Release();
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
			animation.second->Release();
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
