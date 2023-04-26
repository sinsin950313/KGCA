#pragma once

#include <vector>
#include <string>
#include "SerializeableDataType.h"
#include "Matrix.h"

namespace SSB
{
	class SerializeableText
	{
	public:
		std::string _minVertexStr = "Min Vertex\n";
		std::string _maxVertexStr = "Max Vertex\n";
		std::string _socketDataStr = "Socket Data : ";
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
		std::string _isLoopStr = "Is Loop : ";
		std::string _framePerSecondStr = "Frame Per Second : ";
		std::string _boneAnimationUnitMaxCountStr = "Bone Animation Unit Max Count : ";
		std::string _meshAnimationUnitMaxCountStr = "Mesh Animation Unit Max Count : ";
		std::string _startFrameStr = "Start Frame : ";
		std::string _endFrameStr = "End Frame : ";
		std::string _frameInfoPerSecondStr = "Frame Info Per Second\n";
		std::string _maxFrameCountStr = "Max Frame Count : ";
		std::string _frameStr = "Frame : ";

	protected:
		std::string GetTabbedStringText(int tabCount);

	protected:
		std::string SerializeText(int tabCount, int data);
		std::string SerializeText(int tabCount, unsigned int data);
		std::string SerializeText(int tabCount, float data);
		std::string SerializeText(int tabCount, Float2 data);
		std::string SerializeText(int tabCount, Float3 data);
		std::string SerializeText(int tabCount, Float4 data);
		std::string SerializeText(int tabCount, Float33 data);
		std::string SerializeText(int tabCount, Float44 data);
		std::string SerializeText(int tabCount, Vertex_PC data);
		std::string SerializeText(int tabCount, Vertex_PCNT data);
		std::string SerializeText(int tabCount, Vertex_PCNTs data);
		std::string SerializeText(int tabCount, Vertex_PCNT_Skinning data);
		std::string SerializeText(int tabCount, Vertex_PCNTs_Skinning data);
		std::string SerializeText(int tabCount, MeshData data);
		std::string SerializeText(int tabCount, MeshToBoneSpaceTransformData& data, int maxBoneCount);
		std::string SerializeText(int tabCount, AnimationUnitInfo data);
		std::string SerializeText(int tabCount, AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount);

	protected:
		struct ExtractedData
		{
			std::string str;
			int offset;
		};

		ExtractedData GetUnitAtomicText(std::string& str, int offset);
		ExtractedData GetUnitElementText(std::string& str, int offset);
		ExtractedData GetUnitObjectText(std::string& str, int offset);

	protected:
		void DeserializeText(std::string& str, int& ret);
		void DeserializeText(std::string& str, unsigned int& ret);
		void DeserializeText(std::string& str, float& ret);
		void DeserializeText(std::string& str, Float2& ret);
		void DeserializeText(std::string& str, Float3& ret);
		void DeserializeText(std::string& str, Float4& ret);
		void DeserializeText(std::string& str, Float33& ret);
		void DeserializeText(std::string& str, Float44& ret);
		void DeserializeText(std::string& str, Vertex_PC& ret);
		void DeserializeText(std::string& str, Vertex_PCNT& ret);
		void DeserializeText(std::string& str, Vertex_PCNTs& ret);
		void DeserializeText(std::string& str, Vertex_PCNT_Skinning& ret);
		void DeserializeText(std::string& str, Vertex_PCNTs_Skinning& ret);
		void DeserializeText(std::string& str, MeshData& ret);
		void DeserializeText(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount);
		void DeserializeText(std::string& str, AnimationUnitInfo& ret);
		void DeserializeText(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount);

	public:
		virtual std::string SerializeText(int tabCount) = 0;
		virtual void DeserializeText(std::string& serialedString) = 0;
	};

	class SerializeableBinary
	{
	//protected:
	//	std::string SerializeBinary(int data);
	//	std::string SerializeBinary(unsigned int data);
	//	std::string SerializeBinary(float data);
	//	std::string SerializeBinary(Float2 data);
	//	std::string SerializeBinary(Float3 data);
	//	std::string SerializeBinary(Float4 data);
	//	std::string SerializeBinary(Float33 data);
	//	std::string SerializeBinary(Float44 data);
	//	std::string SerializeBinary(Vertex_PC data);
	//	std::string SerializeBinary(Vertex_PCNT data);
	//	std::string SerializeBinary(Vertex_PCNTs data);
	//	std::string SerializeBinary(Vertex_PCNT_Skinning data);
	//	std::string SerializeBinary(Vertex_PCNTs_Skinning data);
	//	std::string SerializeBinary(MeshData data);
	//	std::string SerializeBinary(MeshToBoneSpaceTransformData& data, int maxBoneCount);
	//	std::string SerializeBinary(AnimationUnitInfo data);
	//	std::string SerializeBinary(AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount);

	//protected:
	//	struct ExtractedData
	//	{
	//		std::string str;
	//		int offset;
	//	};

	//	ExtractedData GetUnitAtomicBinary(std::string& str, int offset);
	//	ExtractedData GetUnitElementBinary(std::string& str, int offset);
	//	ExtractedData GetUnitObjectBinary(std::string& str, int offset);

	//protected:
	//	void DeserializeBinary(std::string& str, int& ret);
	//	void DeserializeBinary(std::string& str, unsigned int& ret);
	//	void DeserializeBinary(std::string& str, float& ret);
	//	void DeserializeBinary(std::string& str, Float2& ret);
	//	void DeserializeBinary(std::string& str, Float3& ret);
	//	void DeserializeBinary(std::string& str, Float4& ret);
	//	void DeserializeBinary(std::string& str, Float33& ret);
	//	void DeserializeBinary(std::string& str, Float44& ret);
	//	void DeserializeBinary(std::string& str, Vertex_PC& ret);
	//	void DeserializeBinary(std::string& str, Vertex_PCNT& ret);
	//	void DeserializeBinary(std::string& str, Vertex_PCNTs& ret);
	//	void DeserializeBinary(std::string& str, Vertex_PCNT_Skinning& ret);
	//	void DeserializeBinary(std::string& str, Vertex_PCNTs_Skinning& ret);
	//	void DeserializeBinary(std::string& str, MeshData& ret);
	//	void DeserializeBinary(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount);
	//	void DeserializeBinary(std::string& str, AnimationUnitInfo& ret);
	//	void DeserializeBinary(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount);

	public:
		virtual std::string SerializeBinary() = 0;
		virtual void DeserializeBinary(const char* buffer, int size, int& offset) = 0;
	};
}
