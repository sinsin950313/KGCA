#define _CRT_SECURE_NO_WARNINGS

#include "CharacterTool.h"
#include "InputManager.h"
#include <string>
#include "CommonPath.h"
#include "ShaderManager.h"

namespace SSB
{
	std::vector<ActionData>::iterator CharacterTool::GetIterator(std::string actionName)
	{
		auto iter = _actionList.begin();
		while (iter != _actionList.end())
		{
			if (iter->ActionName == actionName)
			{
				return iter;
			}
			++iter;
		}
		return iter;
	}
	void CharacterTool::Export()
	{
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
			}
		}

		_object->Init();

		_scriptFileName.clear();
		_actionFileName.clear();
	}
	void CharacterTool::RegisterObjectFileName(std::string fileName)
	{
		_objectFileName = fileName;
	}
	void CharacterTool::RegisterScriptFileName(std::string fileName)
	{
		_scriptFileName = fileName;
	}
	void CharacterTool::RegisterActionFileName(std::string fileName)
	{
		_actionFileName = fileName;
	}
	void CharacterTool::ChangeActionName(std::string actionName)
	{
		_selectedActionDataPointer->ActionName = actionName;
	}
	void CharacterTool::SelectCurrentAction(std::string actionName)
	{
		_selectedActionDataPointer = GetIterator(actionName);
		if (_selectedActionDataPointer != _actionList.end())
		{
			_object->UpdateCurrentAnimation(_selectedActionDataPointer->ActionName);
		}
	}
	void CharacterTool::ChangeEndFrame(int frame)
	{
		if (_selectedActionDataPointer != _actionList.end())
		{
			_selectedActionDataPointer->EndFrame = frame;
			std::string currActionName = _selectedActionDataPointer->ActionName;

			const std::string tmpScriptFileName = "TempScript.FBXScript";

			_scriptFileName = tmpScriptFileName;
			Export();

			_actionList.clear();
			Import();

			std::string path = wtm(kFBXScriptPath) + tmpScriptFileName;
			int ret = remove(path.c_str());

			_selectedActionDataPointer = GetIterator(currActionName);
			_object->UpdateCurrentAnimation(_selectedActionDataPointer->ActionName);
		}
	}
	std::vector<ActionData> CharacterTool::GetActionList()
	{
		return _actionList;
	}
	bool CharacterTool::Init()
	{
		_objectFileName.clear();
		_scriptFileName.clear();
		_actionFileName.clear();

		_actionList.clear();
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
