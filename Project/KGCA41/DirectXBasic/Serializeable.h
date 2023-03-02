#pragma once

#include <vector>
#include <string>
#include "SerializeableDataType.h"
#include "Matrix.h"

namespace SSB
{
	class Serializeable
	{
	private:
		std::string GetTabbedString(int tabCount);

	protected:
		std::string Serialize(int tabCount, float data);
		std::string Serialize(int tabCount, Float2 data);
		std::string Serialize(int tabCount, Float3 data);
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
		void DeSerialize(std::string element, float& ret);
		void DeSerialize(std::string element, Float2& ret);
		void DeSerialize(std::string element, Float3& ret);
		void DeSerialize(std::string element, Float33& ret);
		void DeSerialize(std::string element, Float44& ret);
		void DeSerialize(std::string element, Vertex_PC& ret);
		void DeSerialize(std::string element, Vertex_PCNT& ret);
		void DeSerialize(std::string element, Vertex_PCNTs& ret);
		void DeSerialize(std::string element, Vertex_PCNT_Skinning& ret);
		void DeSerialize(std::string element, Vertex_PCNTs_Skinning& ret);
		void DeSerialize(std::string element, MeshData& ret);
		void DeSerialize(std::string element, MeshToBoneSpaceTransformData& ret);
		void DeSerialize(std::string element, AnimationUnitInfo& ret);
		void DeSerialize(std::string element, AnimationFrameInfo& ret);

	public:
		virtual std::vector<std::string> Serialize(int tabCount) = 0;
		virtual void Deserialize() = 0;
	};
}
