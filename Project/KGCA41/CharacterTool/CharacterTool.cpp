#define _CRT_SECURE_NO_WARNINGS

#include "CharacterTool.h"
#include "InputManager.h"
#include <string>
#include "CommonPath.h"
#include "ShaderManager.h"
#include "CommonUtility.h"
#include "Common.h"
#include "Animation.h"
#include "EditableInterface.h"

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

		FILE* fp = fopen((wtm(kFBXScriptPath) + _scriptFileName).c_str(), "w");

		{
			char buffer[256];
			std::string tmp = std::to_string(_actionList.size());
			memcpy(buffer, tmp.c_str(), tmp.size());
			buffer[tmp.size()] = '\n';
			fwrite(buffer, sizeof(decltype(buffer[0])), tmp.size() + 1, fp);
		}
		for (auto action : _actionList)
		{
			if(!action.ActionFileName.empty())
			{
				char buffer[256];
				memcpy(buffer, action.ActionFileName.c_str(), action.ActionFileName.size());
				buffer[action.ActionFileName.size()] = '\t';
				fwrite(buffer, sizeof(decltype(action.ActionFileName[0])), action.ActionFileName.size() + 1, fp);
			}

			{
				char buffer[256];
				memcpy(buffer, action.ActionName.c_str(), action.ActionName.size());
				buffer[action.ActionName.size()] = '\t';
				fwrite(buffer, sizeof(decltype(action.ActionName[0])), action.ActionName.size() + 1, fp);
			}

			{
				char buffer[256];
				std::string tmp = std::to_string(action.EndFrame);
				memcpy(buffer, tmp.c_str(), tmp.size());
				buffer[tmp.size()] = '\n';
				fwrite(buffer, sizeof(decltype(tmp[0])), tmp.size() + 1, fp);
			}
		}

		fclose(fp);
	}
	void CharacterTool::Import()
	{
		_loader->Init();

		_actionList.clear();

		if (_object != nullptr)
		{
			_object->Release();
			delete  _object;
			_object = nullptr;
		}

		if (!_scriptFileName.empty())
		{
			FILE* fp = fopen((wtm(kFBXScriptPath) + _scriptFileName).c_str(), "r");

			int actionCount = 0;
			{
				char buffer[256];
				ZeroMemory(buffer, 256);
				fgets(buffer, 256, fp);
				int bufferLength = strlen(buffer);
				std::string tmp;
				for (int i = 0; i < bufferLength; ++i)
				{
					tmp += buffer[i];
				}
				actionCount = std::stoi(tmp);
			}

			int tabCount = 0;
			std::vector<std::string> actionFileList;
			for (int i = 0; i < actionCount; ++i)
			{
				tabCount = 0;

				char buffer[256];
				ZeroMemory(buffer, 256);
				fgets(buffer, 256, fp);
				int bufferLength = strlen(buffer);

				std::string str[3];
				std::string tmp;
				for (int j = 0; j < bufferLength; ++j)
				{
					if (buffer[j] == '\t')
					{
						str[tabCount] = tmp;
						tmp.clear();
						++tabCount;
					}
					else if (buffer[j] == '\n')
					{
						str[tabCount] = tmp;
					}
					else
					{
						tmp += buffer[j];
					}
				}

				if (tabCount == 1)
				{
					ActionData data;
					data.ActionName = str[0];
					data.EndFrame = std::stoi(str[1]);

					_actionList.push_back(data);
				}

				if (tabCount == 2)
				{
					ActionData data;
					data.ActionFileName = str[0];
					data.ActionName = str[1];
					data.EndFrame = std::stoi(str[2]);

					actionFileList.push_back(str[0]);

					_actionList.push_back(data);
				}
			}

			if (tabCount == 1)
			{
				_object = _loader->Load(_objectFileName, _scriptFileName);
			}
			if (tabCount == 2)
			{
				_object = _loader->Load(_objectFileName, actionFileList, _scriptFileName);
			}

			fclose(fp);
		}
		else if (!_actionFileName.empty())
		{
			_object = _loader->Load(_objectFileName, std::vector<std::string>{ _actionFileName });

			ActionData data;
			data.ActionFileName = _actionFileName;
			data.ActionName = kNewActionName;
			data.EndFrame = _loader->GetEndFrame();
			_actionList.push_back(data);
		}
		else if (_actionFileName.empty())
		{
			_object = _loader->Load(_objectFileName);
			if (_loader->HasAnimation())
			{
				ActionData data;
				data.ActionFileName = _actionFileName;
				data.ActionName = kNewActionName;
				data.EndFrame = _loader->GetEndFrame();
				_actionList.push_back(data);

				Reload();

				SelectCurrentAction(kNewActionName);
			}
		}

		if (_object != nullptr)
		{
			_object->Init();
		_object->UpdatePosition({ 0, 0, 0 });
		}

		_scriptFileName.clear();
		_actionFileName.clear();
	}
	void CharacterTool::RegisterObjectFileName(std::string fileName)
	{
		_objectFileName = fileName;
	}
	void CharacterTool::ClearAnimationSelection()
	{
		{
			_currentAnimation.AnimationPointer = nullptr;
			_currentAnimation.AnimationName.clear();
			_currentAnimation.EndFrame = kEmptyFrame;
		}
	}
	void CharacterTool::RegisterScriptFileName(std::string fileName)
	{
		_scriptFileName = fileName;
	}
	bool CharacterTool::IsSelected()
	{
		return _currentAnimation.AnimationPointer != nullptr;
	}
	void CharacterTool::RegisterActionFileName(std::string fileName)
	{
		_actionFileName = fileName;
	}
	void CharacterTool::AddAction(std::string actionFileName)
	{
		_loader->Init();

		if (_object != nullptr)
		{
			_object->Release();
			delete  _object;
			_object = nullptr;
		}

		_object = _loader->Load(_objectFileName, std::vector<std::string>{ actionFileName });
		_object->Init();
		_object->UpdatePosition({ 0, 0, 0 });

		ActionData data;
		data.ActionFileName = actionFileName;
		data.ActionName = kNewActionName;
		data.EndFrame = _loader->GetEndFrame();
		_actionList.push_back(data);

		Reload();
	}
	void CharacterTool::RemoveAction(std::string actionName)
	{
		auto iter = GetIterator(actionName);
		_actionList.erase(iter);

		Reload();

	}
	void CharacterTool::SelectCurrentAction(std::string actionName)
	{
		ClearAnimationSelection();

		if (_animations.find(actionName) != _animations.end())
		{
			_currentAnimation.AnimationName = actionName;
			_currentAnimation.AnimationPointer = _animations.find(actionName)->second;
			_currentAnimation.EndFrame = _currentAnimation.AnimationPointer->GetFrameSize();
		}
	}
	void CharacterTool::CutAnimataion(std::string newActionName, unsigned int lastFrame)
	{
		if (IsSelected())
		{
			EditableAnimationObject* editableObject = static_cast<EditableAnimationObject*>(_currentAnimation.AnimationPointer->GetEditableObject());
			delete _currentAnimation.AnimationPointer;
			FrameIndex currentEndFrame = editableObject->GetEndFrame();

			{
				editableObject->EditFrame(0, lastFrame);
				Animation* before = editableObject->GetResult();
				_animations.insert(std::make_pair(_currentAnimation.AnimationName, before));
			}

			{
				editableObject->EditFrame(lastFrame, currentEndFrame);
				Animation* after = editableObject->GetResult();
				_animations.insert(std::make_pair(_currentAnimation.AnimationName, after));
			}
		}
	}
	void CharacterTool::ChangeSelectedActionData(std::string actionName, unsigned int frameSize)
	{
		if (IsSelected())
		{
			if (!actionName.empty())
			{
				_animations.erase(_currentAnimation.AnimationName);
				_animations.insert(std::make_pair(actionName, _currentAnimation.AnimationPointer));
			}

			if (frameSize != kEmptyFrame)
			{
				_animations.erase(_currentAnimation.AnimationName);

				EditableAnimationObject* editableObject = static_cast<EditableAnimationObject*>(_currentAnimation.AnimationPointer->GetEditableObject());
				editableObject->EditFrame(0, frameSize);
				editableObject->GetResult();
				delete _currentAnimation.AnimationPointer;

				Animation* result = editableObject->GetResult();
				_currentAnimation.AnimationPointer = result;
				_animations.insert(std::make_pair(_currentAnimation.AnimationName, _currentAnimation.AnimationPointer));
			}

			_currentAnimation.AnimationName = actionName;
			_currentAnimation.EndFrame = frameSize;
		}
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
	DXObject* CharacterTool::GetTargetObject()
	{
		return _object;
	}
	bool CharacterTool::Init()
	{
		if (_model != nullptr)
		{
			_model->Init();
		}

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

		_objectFileName.clear();
		_scriptFileName.clear();
		_actionFileName.clear();

		if (_object != nullptr)
		{
			_object->Release();;
			delete _object;
			_object = nullptr;
		}

		_loader = new FBXLoader();
		_loader->Init();

		return false;
	}
	bool CharacterTool::Frame()
	{
		InputManager::GetInstance().Frame();

		if (_object != nullptr)
		{
			_object->Frame();
		}

		return false;
	}

	bool CharacterTool::Release()
	{
		if (_object != nullptr)
		{
			_object->Release();
			delete _object;
			_object = nullptr;
		}

		if (_loader)
		{
			_loader->Release();
			delete _loader;
			_loader = nullptr;
		}

		return true;
	}

	bool CharacterTool::Render()
	{
		if (_object != nullptr)
		{
			_object->Render();
		}

		return true;
	}
}
