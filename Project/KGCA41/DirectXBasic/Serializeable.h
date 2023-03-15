#pragma once

#include <vector>
#include <string>
#include "SerializeableDataType.h"
#include "Matrix.h"

namespace SSB
{
	class Serializeable
	{
	public:
		std::string _minVertexStr = "Min Vertex\n";
		std::string _maxVertexStr = "Max Vertex\n";
		std::string _boundingVolumeStr = "OBB Data : ";
		std::string _materialStr = "Material\n";
		std::string _materialIndexStr = "Material Index : ";
		std::string _meshStr = "Mesh\n";
		std::string _meshIndexStr = "Mesh Index : ";
		std::string _meshWeightStr = "Mesh Weight : ";
		std::string _animationStr = "Animation\n";
		std::string _animationNameStr = "Animation Name : ";
		std::string _vertexShaderStr = "Vertex Shader File Name : ";
		std::string _pixelShaderStr = "Pixel Shader File Name : ";
		std::string _vertexTypeStr = "Vertex Type : ";
		std::string _vertexListStr = "Vertex List ";
		std::string _indexListStr = "Index List\n";
		std::string _subMeshStr = "SubMesh";
		std::string _meshDataStr = "Mesh Data\n";
		std::string _maxBoneCountStr = "Maximum Bone Count : ";
		std::string _meshToBoneSpaceTransformDataStr = "Mesh to Bone space Transform Data\n";
		std::string _framePerSecondStr = "Frame Per Second : ";
		std::string _boneAnimationUnitMaxCountStr = "Bone Animation Unit Max Count : ";
		std::string _meshAnimationUnitMaxCountStr = "Mesh Animation Unit Max Count : ";
		std::string _startFrameStr = "Start Frame : ";
		std::string _endFrameStr = "End Frame : ";
		std::string _frameInfoPerSecondStr = "Frame Info Per Second\n";
		std::string _maxFrameCountStr = "Max Frame Count : ";
		std::string _frameStr = "Frame : ";

	protected:
		std::string GetTabbedString(int tabCount);

	protected:
		std::string Serialize(int tabCount, int data);
		std::string Serialize(int tabCount, unsigned int data);
		std::string Serialize(int tabCount, float data);
		std::string Serialize(int tabCount, Float2 data);
		std::string Serialize(int tabCount, Float3 data);
		std::string Serialize(int tabCount, Float4 data);
		std::string Serialize(int tabCount, Float33 data);
		std::string Serialize(int tabCount, Float44 data);
		std::string Serialize(int tabCount, Vertex_PC data);
		std::string Serialize(int tabCount, Vertex_PCNT data);
		std::string Serialize(int tabCount, Vertex_PCNTs data);
		std::string Serialize(int tabCount, Vertex_PCNT_Skinning data);
		std::string Serialize(int tabCount, Vertex_PCNTs_Skinning data);
		std::string Serialize(int tabCount, MeshData data);
		std::string Serialize(int tabCount, MeshToBoneSpaceTransformData& data, int maxBoneCount);
		std::string Serialize(int tabCount, AnimationUnitInfo data);
		std::string Serialize(int tabCount, AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount);

	protected:
		struct ExtractedData
		{
			std::string str;
			int offset;
		};

		ExtractedData GetUnitAtomic(std::string& str, int offset);
		ExtractedData GetUnitElement(std::string& str, int offset);
		ExtractedData GetUnitObject(std::string& str, int offset);

	protected:
		void Deserialize(std::string& str, int& ret);
		void Deserialize(std::string& str, unsigned int& ret);
		void Deserialize(std::string& str, float& ret);
		void Deserialize(std::string& str, Float2& ret);
		void Deserialize(std::string& str, Float3& ret);
		void Deserialize(std::string& str, Float4& ret);
		void Deserialize(std::string& str, Float33& ret);
		void Deserialize(std::string& str, Float44& ret);
		void Deserialize(std::string& str, Vertex_PC& ret);
		void Deserialize(std::string& str, Vertex_PCNT& ret);
		void Deserialize(std::string& str, Vertex_PCNTs& ret);
		void Deserialize(std::string& str, Vertex_PCNT_Skinning& ret);
		void Deserialize(std::string& str, Vertex_PCNTs_Skinning& ret);
		void Deserialize(std::string& str, MeshData& ret);
		void Deserialize(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount);
		void Deserialize(std::string& str, AnimationUnitInfo& ret);
		void Deserialize(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount);

	public:
		virtual std::string Serialize(int tabCount) = 0;
		virtual void Deserialize(std::string& serialedString) = 0;
	};
}
