#include "Serializeable.h"

namespace SSB
{
	std::string Serializeable::GetTabbedString(int tabCount)
	{
		std::string ret;
		for (int i = 0; i < tabCount; ++i)
		{
			ret += "\t";
		}
		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, int data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, unsigned int data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, float data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float2 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data.x);
		ret += "\", \"";
		ret += std::to_string(data.y);
		ret += "\"}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float3 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data.x);
		ret += "\", \"";
		ret += std::to_string(data.y);
		ret += "\", \"";
		ret += std::to_string(data.z);
		ret += "\"}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float4 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data.x);
		ret += "\", \"";
		ret += std::to_string(data.y);
		ret += "\", \"";
		ret += std::to_string(data.z);
		ret += "\", \"";
		ret += std::to_string(data.w);
		ret += "\"}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float33 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e11);
		ret += "\", \"";
		ret += std::to_string(data.e12);
		ret += "\", \"";
		ret += std::to_string(data.e13);
		ret += "\",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e21);
		ret += "\", \"";
		ret += std::to_string(data.e22);
		ret += "\", \"";
		ret += std::to_string(data.e23);
		ret += "\",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e31);
		ret += "\", \"";
		ret += std::to_string(data.e32);
		ret += "\", \"";
		ret += std::to_string(data.e33);
		ret += "\",\n";

		ret += GetTabbedString(tabCount);
		ret += "\"}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float44 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e11);
		ret += "\", \"";
		ret += std::to_string(data.e12);
		ret += "\", \"";
		ret += std::to_string(data.e13);
		ret += "\", \"";
		ret += std::to_string(data.e14);
		ret += "\",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e21);
		ret += "\", \"";
		ret += std::to_string(data.e22);
		ret += "\", \"";
		ret += std::to_string(data.e23);
		ret += "\", \"";
		ret += std::to_string(data.e24);
		ret += "\",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e31);
		ret += "\", \"";
		ret += std::to_string(data.e32);
		ret += "\", \"";
		ret += std::to_string(data.e33);
		ret += "\", \"";
		ret += std::to_string(data.e34);
		ret += "\",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e41);
		ret += "\", \"";
		ret += std::to_string(data.e42);
		ret += "\", \"";
		ret += std::to_string(data.e43);
		ret += "\", \"";
		ret += std::to_string(data.e44);
		ret += "\"\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Vertex_PC data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, data.Position);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += "\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Vertex_PCNT data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, data.Position);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += GetTabbedString(tabCount + 1);
		ret += "\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Vertex_PCNTs data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, data.Position);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.MaterialIndex);
		ret += "\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Vertex_PCNT_Skinning data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, data.Position);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "\"}\n";
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.Weight[0]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[1]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[2]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[3]);
		ret += "\"}\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Vertex_PCNTs_Skinning data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, data.Position);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.MaterialIndex);
		ret += "\"}\n";
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "\"}\n";
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.Weight[0]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[1]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[2]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[3]);
		ret += "\"}\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, MeshData data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\"";
		ret += std::to_string(data.MeshIndex);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, MeshToBoneSpaceTransformData& data, int maxBoneCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		for (int i = 0; i < maxBoneCount; ++i)
		{
			ret += Serialize(tabCount + 1, (Float44)data.BoneSpaceTransformBuffer[i]);
			ret += GetTabbedString(tabCount + 1);
			if (i + 1 < maxBoneCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, AnimationUnitInfo data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += Serialize(tabCount + 1, (Float44)data.Matrix);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Translate);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Scale);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serialize(tabCount + 1, (Float4)data.Rotate);
		ret += "\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		for (int i = 0; i < maxBoneCount; ++i)
		{
			ret += Serialize(tabCount + 1, data.BoneAnimationUnit[i]);
			ret += GetTabbedString(tabCount + 1);

			if (i + 1 < maxBoneCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		for (int i = 0; i < maxMeshCount; ++i)
		{
			ret += Serialize(tabCount + 1, data.MeshAnimationUnit[i]);
			ret += GetTabbedString(tabCount + 1);

			if (i + 1 < maxMeshCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	Serializeable::ExtractedData Serializeable::GetUnitAtomic(std::string& str, int offset)
	{
		int startIndex = 0;
		int endIndex = str.size();

		int index = offset;
		while (str[index] != '\"')
		{
			++index;
		}
		++index;

		startIndex = index;

		while (str[index] != '\"')
		{
			++index;
		}
		endIndex = index;

		return { std::string(str.begin() + startIndex, str.begin() + endIndex), index + 1 };
	}
	Serializeable::ExtractedData Serializeable::GetUnitElement(std::string& str, int offset)
	{
		int startIndex = 0;
		int endIndex = str.size();
		int count = 0;
		bool begin = false;
		for (int i = offset; i < str.size(); ++i)
		{
			if (!begin && str[i] == '{')
			{
				startIndex = i;
				begin = true;
			}

			if (str[i] == '{')
			{
				++count;
			}
			if (str[i] == '}')
			{
				--count;
			}

			if (begin && count == 0)
			{
				endIndex = i;
				break;
			}
		}

		//if (endIndex == str.size())
		//{
		//	return std::string(str.begin() + startIndex, str.begin() + endIndex);
		//}
		//else
		//{
		return { std::string(str.begin() + startIndex, str.begin() + endIndex + 1), endIndex + 1 };
		//}
	}
	Serializeable::ExtractedData Serializeable::GetUnitObject(std::string& str, int offset)
	{
		int startIndex = 0;
		int endIndex = str.size();
		int count = 0;
		bool begin = false;
		for (int i = offset; i < str.size(); ++i)
		{
			if (!begin && str[i] == '[')
			{
				startIndex = i;
				begin = true;
			}

			if (str[i] == '[')
			{
				++count;
			}
			if (str[i] == ']')
			{
				--count;
			}

			if (begin && count == 0)
			{
				endIndex = i;
				break;
			}
		}

		//if (endIndex == str.size())
		//{
		//	return std::string(str.begin() + startIndex, str.begin() + endIndex);
		//}
		//else
		//{
		return { std::string(str.begin() + startIndex, str.begin() + endIndex + 1), endIndex + 1 };
		//}
	}
	void Serializeable::Deserialize(std::string& str, int& ret)
	{
		str = GetUnitElement(str, 0).str;
		auto val = GetUnitAtomic(str, 0);
		ret = std::stoi(val.str);
	}
	void Serializeable::Deserialize(std::string& str, unsigned int& ret)
	{
		str = GetUnitElement(str, 0).str;
		auto val = GetUnitAtomic(str, 0);
		ret = std::stoul(val.str);
	}
	void Serializeable::Deserialize(std::string& str, float& ret)
	{
		str = GetUnitElement(str, 0).str;
		auto val = GetUnitAtomic(str, 0);
		ret = std::stof(val.str);
	}
	void Serializeable::Deserialize(std::string& str, Float2& ret)
	{
		str = GetUnitElement(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 2; ++i)
		{
			auto data = GetUnitAtomic(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void Serializeable::Deserialize(std::string& str, Float3& ret)
	{
		str = GetUnitElement(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 3; ++i)
		{
			auto data = GetUnitAtomic(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void Serializeable::Deserialize(std::string& str, Float4& ret)
	{
		str = GetUnitElement(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 4; ++i)
		{
			auto data = GetUnitAtomic(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void Serializeable::Deserialize(std::string& str, Float33& ret)
	{
		float val[9];

		str = GetUnitElement(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				auto data = GetUnitAtomic(str, offset);
				std::string valStr = data.str;
				offset = data.offset;
				val[i * 3 + j] = std::stof(valStr);
			}
		}

		ret = {
			val[0], val[1], val[2],
			val[3], val[4], val[5],
			val[6], val[7], val[8]
		};
	}
	void Serializeable::Deserialize(std::string& str, Float44& ret)
	{
		float val[16] = { 0, };

		str = GetUnitElement(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				auto data = GetUnitAtomic(str, offset);
				std::string valStr = data.str;
				offset = data.offset;
				val[i * 4 + j] = std::stof(valStr);
			}
		}

		ret = {
			val[0], val[1], val[2], val[3],
			val[4], val[5], val[6], val[7],
			val[8], val[9], val[10], val[11],
			val[12], val[13], val[14], val[15]
		};
	}
	void Serializeable::Deserialize(std::string& str, Vertex_PC& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Position);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Color);
		}
	}
	void Serializeable::Deserialize(std::string& str, Vertex_PCNT& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset += data.offset;
			Deserialize(elem, ret.Position);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Color);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Normal);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.TextureUV);
		}
	}
	void Serializeable::Deserialize(std::string& str, Vertex_PCNTs& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Position);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Color);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Normal);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.TextureUV);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.MaterialIndex);
		}
	}
	void Serializeable::Deserialize(std::string& str, Vertex_PCNT_Skinning& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Position);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Color);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.Normal);
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.TextureUV);
		}

		{
			{
				auto data = GetUnitElement(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				Deserialize(elem, tmp);
				ret.AffectedBoneIndex[0] = tmp.x;
				ret.AffectedBoneIndex[1] = tmp.y;
				ret.AffectedBoneIndex[2] = tmp.z;
				ret.AffectedBoneIndex[3] = tmp.w;
			}
		}

		{
			{
				auto data = GetUnitElement(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				Deserialize(elem, tmp);
				ret.Weight[0] = tmp.x;
				ret.Weight[1] = tmp.y;
				ret.Weight[2] = tmp.z;
				ret.Weight[3] = tmp.w;
			}
		}
	}
	void Serializeable::Deserialize(std::string& str, Vertex_PCNTs_Skinning& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			Deserialize(elem, ret.Position);
			offset = data.offset;
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			Deserialize(elem, ret.Color);
			offset = data.offset;
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			Deserialize(elem, ret.Normal);
			offset = data.offset;
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			Deserialize(elem, ret.TextureUV);
			offset = data.offset;
		}

		{
			auto data = GetUnitElement(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			Deserialize(elem, ret.MaterialIndex);
		}

		{
			{
				auto data = GetUnitElement(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				Deserialize(elem, tmp);
				ret.AffectedBoneIndex[0] = tmp.x;
				ret.AffectedBoneIndex[1] = tmp.y;
				ret.AffectedBoneIndex[2] = tmp.z;
				ret.AffectedBoneIndex[3] = tmp.w;
			}
		}

		{
			{
				auto data = GetUnitElement(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				Deserialize(elem, tmp);
				ret.Weight[0] = tmp.x;
				ret.Weight[1] = tmp.y;
				ret.Weight[2] = tmp.z;
				ret.Weight[3] = tmp.w;
			}
		}
	}
	void Serializeable::Deserialize(std::string& str, MeshData& ret)
	{
		auto data = GetUnitElement(str, 0);
		std::string elem = data.str;
		Deserialize(elem, ret.MeshIndex);
	}
	void Serializeable::Deserialize(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount)
	{
		auto data = GetUnitElement(str, 0);
		std::string elem = data.str;
		int offset = 1;
		for (int i = 0; i < maxBoneCount; ++i)
		{
			auto valData = GetUnitElement(elem, offset);
			std::string val = valData.str;
			offset = valData.offset;

			Float44 tmp;
			Deserialize(val, tmp);
			ret.BoneSpaceTransformBuffer[i] = {
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44,
			};
		}
	}
	void Serializeable::Deserialize(std::string& str, AnimationUnitInfo& ret)
	{
		auto data = GetUnitElement(str, 0);
		std::string elem = data.str;

		int offset = 1;
		{
			auto localElemData = GetUnitElement(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float44 val;
			Deserialize(localElem, val);
			ret.Matrix = {
				val.e11, val.e12, val.e13, val.e14,
				val.e21, val.e22, val.e23, val.e24,
				val.e31, val.e32, val.e33, val.e34,
				val.e41, val.e42, val.e43, val.e44,
			};
		}

		{
			auto localElemData = GetUnitElement(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float3 val;
			Deserialize(localElem, val);
			ret.Translate = { val.x, val.y, val.z };
		}

		{
			auto localElemData = GetUnitElement(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float3 val;
			Deserialize(localElem, val);
			ret.Scale = { val.x, val.y, val.z };
		}

		{
			auto localElemData = GetUnitElement(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float4 val;
			Deserialize(localElem, val);
			ret.Rotate = { val.x, val.y, val.z, val.w };
		}
	}
	void Serializeable::Deserialize(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount)
	{
		str = GetUnitElement(str, 0).str;

		int offset = 1;
		for (int i = 0; i < maxBoneCount; ++i)
		{
			auto data = GetUnitElement(str, offset);
			std::string val = data.str;
			offset = data.offset;
			Deserialize(val, ret.BoneAnimationUnit[i]);
		}

		for (int i = 0; i < maxMeshCount; ++i)
		{
			auto data = GetUnitElement(str, offset);
			std::string val = data.str;
			offset = data.offset;
			Deserialize(val, ret.MeshAnimationUnit[i]);
		}
	}
}