#pragma once

#include "Common.h"
#include <fbxsdk.h>
#include <vector>
#include "DXObject.h"

namespace SSB
{
	class FBXLoader : public Common
	{
	private:
		std::string _fileName;
		FbxManager* _manager;
		FbxImporter* _importer;
		FbxScene* _scene;
		FbxNode* _root;
		std::vector<FbxMesh*> _meshList;

	public:
		std::vector<DXObject*> _objectList;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void Load();
		void PreProcess(FbxNode* node);
		void ParseMesh(FbxMesh* mesh);
		FbxVector2 ReadTextureCoordinate(FbxLayerElementUV* texture, int posIndex, int uvIndex);
		FbxColor ReadColor(FbxLayerElementVertexColor* vertexColor, int posIndex, int colorIndex);

	public:
		void SetFileName(std::string fileName) { _fileName = fileName; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
