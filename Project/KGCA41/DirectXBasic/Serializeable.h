#pragma once

#include <vector>
#include <string>
#include "SerializeableDataType.h"
#include "Matrix.h"

namespace SSB
{
	class Serializeable
	{
	protected:
		std::string GetTabbedString(int tabCount);

	protected:
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
		std::string Serialize(int tabCount, MeshToBoneSpaceTransformData& data);
		std::string Serialize(int tabCount, AnimationUnitInfo data);
		std::string Serialize(int tabCount, AnimationFrameInfo& data);

	protected:
		std::string GetUnitObject(std::string str, int offset);
		std::string GetUnitElement(std::string str, int offset);

	protected:
		void Deserialize(std::string element, int& ret);
		void Deserialize(std::string element, unsigned int& ret);
		void Deserialize(std::string element, float& ret);
		void Deserialize(std::string element, Float2& ret);
		void Deserialize(std::string element, Float3& ret);
		void Deserialize(std::string element, Float33& ret);
		void Deserialize(std::string element, Float44& ret);
		void Deserialize(std::string element, Vertex_PC& ret);
		void Deserialize(std::string element, Vertex_PCNT& ret);
		void Deserialize(std::string element, Vertex_PCNTs& ret);
		void Deserialize(std::string element, Vertex_PCNT_Skinning& ret);
		void Deserialize(std::string element, Vertex_PCNTs_Skinning& ret);
		void Deserialize(std::string element, MeshData& ret);
		void Deserialize(std::string element, MeshToBoneSpaceTransformData& ret);
		void Deserialize(std::string element, AnimationUnitInfo& ret);
		void Deserialize(std::string element, AnimationFrameInfo& ret);

	public:
		virtual std::string Serialize(int tabCount) = 0;
		virtual void Deserialize(std::string serialedString) = 0;
	};
}
