#include "Serializeable.h"

namespace SSB
{
	std::string SerializeableText::GetTabbedStringText(int tabCount)
	{
		std::string ret;
		for (int i = 0; i < tabCount; ++i)
		{
			ret += "\t";
		}
		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, int data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, unsigned int data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, float data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Float2 data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data.x);
		ret += "\", \"";
		ret += std::to_string(data.y);
		ret += "\"}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Float3 data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data.x);
		ret += "\", \"";
		ret += std::to_string(data.y);
		ret += "\", \"";
		ret += std::to_string(data.z);
		ret += "\"}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Float4 data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
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
	std::string SerializeableText::SerializeText(int tabCount, Float33 data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e11);
		ret += "\", \"";
		ret += std::to_string(data.e12);
		ret += "\", \"";
		ret += std::to_string(data.e13);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e21);
		ret += "\", \"";
		ret += std::to_string(data.e22);
		ret += "\", \"";
		ret += std::to_string(data.e23);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e31);
		ret += "\", \"";
		ret += std::to_string(data.e32);
		ret += "\", \"";
		ret += std::to_string(data.e33);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount);
		ret += "\"}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Float44 data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e11);
		ret += "\", \"";
		ret += std::to_string(data.e12);
		ret += "\", \"";
		ret += std::to_string(data.e13);
		ret += "\", \"";
		ret += std::to_string(data.e14);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e21);
		ret += "\", \"";
		ret += std::to_string(data.e22);
		ret += "\", \"";
		ret += std::to_string(data.e23);
		ret += "\", \"";
		ret += std::to_string(data.e24);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e31);
		ret += "\", \"";
		ret += std::to_string(data.e32);
		ret += "\", \"";
		ret += std::to_string(data.e33);
		ret += "\", \"";
		ret += std::to_string(data.e34);
		ret += "\",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "\"";
		ret += std::to_string(data.e41);
		ret += "\", \"";
		ret += std::to_string(data.e42);
		ret += "\", \"";
		ret += std::to_string(data.e43);
		ret += "\", \"";
		ret += std::to_string(data.e44);
		ret += "\"\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Vertex_PC data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, data.Position);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Color);
		ret += "\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Vertex_PCNT data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, data.Position);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Color);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Normal);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.TextureUV);
		ret += GetTabbedStringText(tabCount + 1);
		ret += "\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Vertex_PCNTs data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, data.Position);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Color);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Normal);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.TextureUV);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.MaterialIndex);
		ret += "\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Vertex_PCNT_Skinning data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, data.Position);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Color);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Normal);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.TextureUV);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "\"}\n";
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.Weight[0]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[1]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[2]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[3]);
		ret += "\"}\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, Vertex_PCNTs_Skinning data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, data.Position);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Color);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Normal);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.TextureUV);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.MaterialIndex);
		ret += "\"}\n";
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += "\", \"";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "\"}\n";
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += "{\"";
		ret += std::to_string(data.Weight[0]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[1]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[2]);
		ret += "\", \"";
		ret += std::to_string(data.Weight[3]);
		ret += "\"}\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, MeshData data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\"";
		ret += std::to_string(data.MeshIndex);
		ret += "\"}";
		ret += "\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, MeshToBoneSpaceTransformData& data, int maxBoneCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		for (int i = 0; i < maxBoneCount; ++i)
		{
			ret += SerializeText(tabCount + 1, (Float44)data.BoneSpaceTransformBuffer[i]);
			ret += GetTabbedStringText(tabCount + 1);
			if (i + 1 < maxBoneCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, AnimationUnitInfo data)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		ret += SerializeText(tabCount + 1, (Float44)data.Matrix);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Translate);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, data.Scale);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeText(tabCount + 1, (Float4)data.Rotate);
		ret += "\n";

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string SerializeableText::SerializeText(int tabCount, AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "{\n";

		for (int i = 0; i < maxBoneCount; ++i)
		{
			ret += SerializeText(tabCount + 1, data.BoneAnimationUnit[i]);
			ret += GetTabbedStringText(tabCount + 1);

			if (i + 1 < maxBoneCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		for (int i = 0; i < maxMeshCount; ++i)
		{
			ret += SerializeText(tabCount + 1, data.MeshAnimationUnit[i]);
			ret += GetTabbedStringText(tabCount + 1);

			if (i + 1 < maxMeshCount)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}

		ret += GetTabbedStringText(tabCount);
		ret += "}\n";

		return ret;
	}
	SerializeableText::ExtractedData SerializeableText::GetUnitAtomicText(std::string& str, int offset)
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
	SerializeableText::ExtractedData SerializeableText::GetUnitElementText(std::string& str, int offset)
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
	SerializeableText::ExtractedData SerializeableText::GetUnitObjectText(std::string& str, int offset)
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
	void SerializeableText::DeserializeText(std::string& str, int& ret)
	{
		str = GetUnitElementText(str, 0).str;
		auto val = GetUnitAtomicText(str, 0);
		ret = std::stoi(val.str);
	}
	void SerializeableText::DeserializeText(std::string& str, unsigned int& ret)
	{
		str = GetUnitElementText(str, 0).str;
		auto val = GetUnitAtomicText(str, 0);
		ret = std::stoul(val.str);
	}
	void SerializeableText::DeserializeText(std::string& str, float& ret)
	{
		str = GetUnitElementText(str, 0).str;
		auto val = GetUnitAtomicText(str, 0);
		ret = std::stof(val.str);
	}
	void SerializeableText::DeserializeText(std::string& str, Float2& ret)
	{
		str = GetUnitElementText(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 2; ++i)
		{
			auto data = GetUnitAtomicText(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Float3& ret)
	{
		str = GetUnitElementText(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 3; ++i)
		{
			auto data = GetUnitAtomicText(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Float4& ret)
	{
		str = GetUnitElementText(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 4; ++i)
		{
			auto data = GetUnitAtomicText(str, offset);
			std::string val = data.str;
			offset = data.offset;
			ret.e[i] = std::stof(val);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Float33& ret)
	{
		float val[9];

		str = GetUnitElementText(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				auto data = GetUnitAtomicText(str, offset);
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
	void SerializeableText::DeserializeText(std::string& str, Float44& ret)
	{
		float val[16] = { 0, };

		str = GetUnitElementText(str, 0).str;
		int offset = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				auto data = GetUnitAtomicText(str, offset);
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
	void SerializeableText::DeserializeText(std::string& str, Vertex_PC& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Position);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Color);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Vertex_PCNT& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset += data.offset;
			DeserializeText(elem, ret.Position);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Color);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Normal);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.TextureUV);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Vertex_PCNTs& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Position);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Color);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Normal);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.TextureUV);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.MaterialIndex);
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Vertex_PCNT_Skinning& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Position);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Color);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.Normal);
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.TextureUV);
		}

		{
			{
				auto data = GetUnitElementText(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				DeserializeText(elem, tmp);
				ret.AffectedBoneIndex[0] = tmp.x;
				ret.AffectedBoneIndex[1] = tmp.y;
				ret.AffectedBoneIndex[2] = tmp.z;
				ret.AffectedBoneIndex[3] = tmp.w;
			}
		}

		{
			{
				auto data = GetUnitElementText(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				DeserializeText(elem, tmp);
				ret.Weight[0] = tmp.x;
				ret.Weight[1] = tmp.y;
				ret.Weight[2] = tmp.z;
				ret.Weight[3] = tmp.w;
			}
		}
	}
	void SerializeableText::DeserializeText(std::string& str, Vertex_PCNTs_Skinning& ret)
	{
		int offset = 1;
		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			DeserializeText(elem, ret.Position);
			offset = data.offset;
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			DeserializeText(elem, ret.Color);
			offset = data.offset;
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			DeserializeText(elem, ret.Normal);
			offset = data.offset;
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			DeserializeText(elem, ret.TextureUV);
			offset = data.offset;
		}

		{
			auto data = GetUnitElementText(str, offset);
			std::string elem = data.str;
			offset = data.offset;
			DeserializeText(elem, ret.MaterialIndex);
		}

		{
			{
				auto data = GetUnitElementText(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				DeserializeText(elem, tmp);
				ret.AffectedBoneIndex[0] = tmp.x;
				ret.AffectedBoneIndex[1] = tmp.y;
				ret.AffectedBoneIndex[2] = tmp.z;
				ret.AffectedBoneIndex[3] = tmp.w;
			}
		}

		{
			{
				auto data = GetUnitElementText(str, offset);
				std::string elem = data.str;
				offset = data.offset;

				Float4 tmp;
				DeserializeText(elem, tmp);
				ret.Weight[0] = tmp.x;
				ret.Weight[1] = tmp.y;
				ret.Weight[2] = tmp.z;
				ret.Weight[3] = tmp.w;
			}
		}
	}
	void SerializeableText::DeserializeText(std::string& str, MeshData& ret)
	{
		auto data = GetUnitElementText(str, 0);
		std::string elem = data.str;
		DeserializeText(elem, ret.MeshIndex);
	}
	void SerializeableText::DeserializeText(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount)
	{
		auto data = GetUnitElementText(str, 0);
		std::string elem = data.str;
		int offset = 1;
		for (int i = 0; i < maxBoneCount; ++i)
		{
			auto valData = GetUnitElementText(elem, offset);
			std::string val = valData.str;
			offset = valData.offset;

			Float44 tmp;
			DeserializeText(val, tmp);
			ret.BoneSpaceTransformBuffer[i] = {
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44,
			};
		}
	}
	void SerializeableText::DeserializeText(std::string& str, AnimationUnitInfo& ret)
	{
		auto data = GetUnitElementText(str, 0);
		std::string elem = data.str;

		int offset = 1;
		{
			auto localElemData = GetUnitElementText(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float44 val;
			DeserializeText(localElem, val);
			ret.Matrix = {
				val.e11, val.e12, val.e13, val.e14,
				val.e21, val.e22, val.e23, val.e24,
				val.e31, val.e32, val.e33, val.e34,
				val.e41, val.e42, val.e43, val.e44,
			};
		}

		{
			auto localElemData = GetUnitElementText(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float3 val;
			DeserializeText(localElem, val);
			ret.Translate = { val.x, val.y, val.z };
		}

		{
			auto localElemData = GetUnitElementText(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float3 val;
			DeserializeText(localElem, val);
			ret.Scale = { val.x, val.y, val.z };
		}

		{
			auto localElemData = GetUnitElementText(elem, offset);
			std::string localElem = localElemData.str;
			offset = localElemData.offset;
			Float4 val;
			DeserializeText(localElem, val);
			ret.Rotate = { val.x, val.y, val.z, val.w };
		}
	}
	void SerializeableText::DeserializeText(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount)
	{
		str = GetUnitElementText(str, 0).str;

		int offset = 1;
		for (int i = 0; i < maxBoneCount; ++i)
		{
			auto data = GetUnitElementText(str, offset);
			std::string val = data.str;
			offset = data.offset;
			DeserializeText(val, ret.BoneAnimationUnit[i]);
		}

		for (int i = 0; i < maxMeshCount; ++i)
		{
			auto data = GetUnitElementText(str, offset);
			std::string val = data.str;
			offset = data.offset;
			DeserializeText(val, ret.MeshAnimationUnit[i]);
		}
	}
	//std::string SerializeableBinary::GetSerializeableKeyword(SerializableBinaryKeyword keyword)
	//{
	//	std::string ret = "가나다라마바사" + keyword;
	//	ret = ret + "아자차카타파하";
	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(int data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += data;
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(unsigned int data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(float data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Float2 data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data.x);
	//	ret += "\", \"";
	//	ret += (data.y);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Float3 data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data.x);
	//	ret += "\", \"";
	//	ret += (data.y);
	//	ret += "\", \"";
	//	ret += (data.z);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Float4 data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data.x);
	//	ret += "\", \"";
	//	ret += (data.y);
	//	ret += "\", \"";
	//	ret += (data.z);
	//	ret += "\", \"";
	//	ret += (data.w);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Float33 data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += "\"";
	//	ret += (data.e11);
	//	ret += "\", \"";
	//	ret += (data.e12);
	//	ret += "\", \"";
	//	ret += (data.e13);
	//	//ret += "\",";
	//	ret += "\",";

	//	ret += "\"";
	//	ret += (data.e21);
	//	ret += "\", \"";
	//	ret += (data.e22);
	//	ret += "\", \"";
	//	ret += (data.e23);
	//	//ret += "\",";
	//	ret += "\",";

	//	ret += "\"";
	//	ret += (data.e31);
	//	ret += "\", \"";
	//	ret += (data.e32);
	//	ret += "\", \"";
	//	ret += (data.e33);
	//	//ret += "\",";
	//	ret += "\",";

	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Float44 data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += "\"";
	//	ret += (data.e11);
	//	ret += "\", \"";
	//	ret += (data.e12);
	//	ret += "\", \"";
	//	ret += (data.e13);
	//	ret += "\", \"";
	//	ret += (data.e14);
	//	ret += "\",";

	//	ret += "\"";
	//	ret += (data.e21);
	//	ret += "\", \"";
	//	ret += (data.e22);
	//	ret += "\", \"";
	//	ret += (data.e23);
	//	ret += "\", \"";
	//	ret += (data.e24);
	//	ret += "\",";

	//	ret += "\"";
	//	ret += (data.e31);
	//	ret += "\", \"";
	//	ret += (data.e32);
	//	ret += "\", \"";
	//	ret += (data.e33);
	//	ret += "\", \"";
	//	ret += (data.e34);
	//	//ret += "\",";
	//	ret += "\",";

	//	ret += "\"";
	//	ret += (data.e41);
	//	ret += "\", \"";
	//	ret += (data.e42);
	//	ret += "\", \"";
	//	ret += (data.e43);
	//	ret += "\", \"";
	//	ret += (data.e44);
	//	ret += "\"";

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Vertex_PC data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary(data.Position);
	//	ret += ",";

	//	ret += SerializeBinary(data.Color);

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Vertex_PCNT data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary(data.Position);
	//	ret += ",";

	//	ret += SerializeBinary(data.Color);
	//	ret += ",";

	//	ret += SerializeBinary(data.Normal);
	//	ret += ",";

	//	ret += SerializeBinary(data.TextureUV);

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Vertex_PCNTs data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary(data.Position);
	//	ret += ",";

	//	ret += SerializeBinary(data.Color);
	//	ret += ",";

	//	ret += SerializeBinary(data.Normal);
	//	ret += ",";

	//	ret += SerializeBinary(data.TextureUV);
	//	ret += ",";

	//	ret += SerializeBinary(data.MaterialIndex);
	//	ret += "";

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Vertex_PCNT_Skinning data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary(data.Position);
	//	ret += ",";

	//	ret += SerializeBinary(data.Color);
	//	ret += ",";

	//	ret += SerializeBinary(data.Normal);
	//	ret += ",";

	//	ret += SerializeBinary(data.TextureUV);
	//	ret += ",";

	//	ret += "{\"";
	//	ret += (data.AffectedBoneIndex[0]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[1]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[2]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[3]);
	//	ret += "\"}";
	//	ret += ",";

	//	ret += "{\"";
	//	ret += (data.Weight[0]);
	//	ret += "\", \"";
	//	ret += (data.Weight[1]);
	//	ret += "\", \"";
	//	ret += (data.Weight[2]);
	//	ret += "\", \"";
	//	ret += (data.Weight[3]);
	//	ret += "\"}";

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(Vertex_PCNTs_Skinning data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary(data.Position);
	//	ret += ",";

	//	ret += SerializeBinary(data.Color);
	//	ret += ",";

	//	ret += SerializeBinary(data.Normal);
	//	ret += ",";

	//	ret += SerializeBinary(data.TextureUV);
	//	ret += ",";

	//	ret += "{\"";
	//	ret += (data.MaterialIndex);
	//	ret += "\"}";
	//	ret += ",";

	//	ret += "{\"";
	//	ret += (data.AffectedBoneIndex[0]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[1]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[2]);
	//	ret += "\", \"";
	//	ret += (data.AffectedBoneIndex[3]);
	//	ret += "\"}";
	//	ret += ",";

	//	ret += "{\"";
	//	ret += (data.Weight[0]);
	//	ret += "\", \"";
	//	ret += (data.Weight[1]);
	//	ret += "\", \"";
	//	ret += (data.Weight[2]);
	//	ret += "\", \"";
	//	ret += (data.Weight[3]);
	//	ret += "\"}";

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(MeshData data)
	//{
	//	std::string ret;

	//	ret += "{\"";
	//	ret += (data.MeshIndex);
	//	ret += "\"}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(MeshToBoneSpaceTransformData& data, int maxBoneCount)
	//{
	//	std::string ret;

	//	ret += "{";

	//	for (int i = 0; i < maxBoneCount; ++i)
	//	{
	//		ret += SerializeBinary((Float44)data.BoneSpaceTransformBuffer[i]);
	//		if (i + 1 < maxBoneCount)
	//		{
	//			ret += ",";
	//		}
	//		else
	//		{
	//			ret += "";
	//		}
	//	}

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(AnimationUnitInfo data)
	//{
	//	std::string ret;

	//	ret += "{";

	//	ret += SerializeBinary((Float44)data.Matrix);
	//	ret += ",";

	//	ret += SerializeBinary(data.Translate);
	//	ret += ",";

	//	ret += SerializeBinary(data.Scale);
	//	ret += ",";

	//	ret += SerializeBinary((Float4)data.Rotate);
	//	ret += "";

	//	ret += "}";

	//	return ret;
	//}
	//std::string SerializeableBinary::SerializeBinary(AnimationFrameInfo& data, int maxBoneCount, int maxMeshCount)
	//{
	//	std::string ret;

	//	ret += "{";

	//	for (int i = 0; i < maxBoneCount; ++i)
	//	{
	//		ret += SerializeBinary(data.BoneAnimationUnit[i]);

	//		if (i + 1 < maxBoneCount)
	//		{
	//			ret += ",";
	//		}
	//		else
	//		{
	//			ret += "";
	//		}
	//	}
	//	ret += ",";

	//	for (int i = 0; i < maxMeshCount; ++i)
	//	{
	//		ret += SerializeBinary(data.MeshAnimationUnit[i]);

	//		if (i + 1 < maxMeshCount)
	//		{
	//			ret += ",";
	//		}
	//		else
	//		{
	//			ret += "";
	//		}
	//	}

	//	ret += "}";

	//	return ret;
	//}
	//SerializeableBinary::ExtractedData SerializeableBinary::GetUnitAtomicBinary(std::string& str, int offset)
	//{
	//	int startIndex = 0;
	//	int endIndex = str.size();

	//	int index = offset;
	//	while (str[index] != '\"')
	//	{
	//		++index;
	//	}
	//	++index;

	//	startIndex = index;

	//	while (str[index] != '\"')
	//	{
	//		++index;
	//	}
	//	endIndex = index;

	//	return { std::string(str.begin() + startIndex, str.begin() + endIndex), index + 1 };
	//}
	//SerializeableBinary::ExtractedData SerializeableBinary::GetUnitElementBinary(std::string& str, int offset)
	//{
	//	int startIndex = 0;
	//	int endIndex = str.size();
	//	int count = 0;
	//	bool begin = false;
	//	for (int i = offset; i < str.size(); ++i)
	//	{
	//		if (!begin && str[i] == '{')
	//		{
	//			startIndex = i;
	//			begin = true;
	//		}

	//		if (str[i] == '{')
	//		{
	//			++count;
	//		}
	//		if (str[i] == '}')
	//		{
	//			--count;
	//		}

	//		if (begin && count == 0)
	//		{
	//			endIndex = i;
	//			break;
	//		}
	//	}

	//	//if (endIndex == str.size())
	//	//{
	//	//	return std::string(str.begin() + startIndex, str.begin() + endIndex);
	//	//}
	//	//else
	//	//{
	//	return { std::string(str.begin() + startIndex, str.begin() + endIndex + 1), endIndex + 1 };
	//	//}
	//}
	//SerializeableBinary::ExtractedData SerializeableBinary::GetUnitObjectBinary(std::string& str, int offset)
	//{
	//	int startIndex = 0;
	//	int endIndex = str.size();
	//	int count = 0;
	//	bool begin = false;
	//	for (int i = offset; i < str.size(); ++i)
	//	{
	//		if (!begin && str[i] == '[')
	//		{
	//			startIndex = i;
	//			begin = true;
	//		}

	//		if (str[i] == '[')
	//		{
	//			++count;
	//		}
	//		if (str[i] == ']')
	//		{
	//			--count;
	//		}

	//		if (begin && count == 0)
	//		{
	//			endIndex = i;
	//			break;
	//		}
	//	}

	//	//if (endIndex == str.size())
	//	//{
	//	//	return std::string(str.begin() + startIndex, str.begin() + endIndex);
	//	//}
	//	//else
	//	//{
	//	return { std::string(str.begin() + startIndex, str.begin() + endIndex + 1), endIndex + 1 };
	//	//}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, int& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	auto val = GetUnitAtomicBinary(str, 0);
	//	ret = (int)val.str[0];
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, unsigned int& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	auto val = GetUnitAtomicBinary(str, 0);
	//	ret = (unsigned int)val.str[0];
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, float& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	auto val = GetUnitAtomicBinary(str, 0);
	//	ret = (float)val.str[0];
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Float2& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	int offset = 0;
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		auto data = GetUnitAtomicBinary(str, offset);
	//		std::string val = data.str;
	//		offset = data.offset;
	//		ret.e[i] = (float)val[0];
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Float3& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	int offset = 0;
	//	for (int i = 0; i < 3; ++i)
	//	{
	//		auto data = GetUnitAtomicBinary(str, offset);
	//		std::string val = data.str;
	//		offset = data.offset;
	//		ret.e[i] = (float)val[0];
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Float4& ret)
	//{
	//	str = GetUnitElementBinary(str, 0).str;
	//	int offset = 0;
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		auto data = GetUnitAtomicBinary(str, offset);
	//		std::string val = data.str;
	//		offset = data.offset;
	//		ret.e[i] = (float)val[0];
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Float33& ret)
	//{
	//	float val[9];

	//	str = GetUnitElementBinary(str, 0).str;
	//	int offset = 0;
	//	for (int i = 0; i < 3; ++i)
	//	{
	//		for (int j = 0; j < 3; ++j)
	//		{
	//			auto data = GetUnitAtomicBinary(str, offset);
	//			std::string valStr = data.str;
	//			offset = data.offset;
	//			val[i * 3 + j] = (float)valStr[0];
	//		}
	//	}

	//	ret = {
	//		val[0], val[1], val[2],
	//		val[3], val[4], val[5],
	//		val[6], val[7], val[8]
	//	};
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Float44& ret)
	//{
	//	float val[16] = { 0, };

	//	str = GetUnitElementBinary(str, 0).str;
	//	int offset = 0;
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		for (int j = 0; j < 4; ++j)
	//		{
	//			auto data = GetUnitAtomicBinary(str, offset);
	//			std::string valStr = data.str;
	//			offset = data.offset;
	//			val[i * 4 + j] = (float)valStr[0];
	//		}
	//	}

	//	ret = {
	//		val[0], val[1], val[2], val[3],
	//		val[4], val[5], val[6], val[7],
	//		val[8], val[9], val[10], val[11],
	//		val[12], val[13], val[14], val[15]
	//	};
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Vertex_PC& ret)
	//{
	//	int offset = 1;
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Position);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Color);
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Vertex_PCNT& ret)
	//{
	//	int offset = 1;
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset += data.offset;
	//		DeserializeBinary(elem, ret.Position);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Color);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Normal);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.TextureUV);
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Vertex_PCNTs& ret)
	//{
	//	int offset = 1;
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Position);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Color);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Normal);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.TextureUV);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.MaterialIndex);
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Vertex_PCNT_Skinning& ret)
	//{
	//	int offset = 1;
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Position);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Color);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.Normal);
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.TextureUV);
	//	}

	//	{
	//		{
	//			auto data = GetUnitElementBinary(str, offset);
	//			std::string elem = data.str;
	//			offset = data.offset;

	//			Float4 tmp;
	//			DeserializeBinary(elem, tmp);
	//			ret.AffectedBoneIndex[0] = tmp.x;
	//			ret.AffectedBoneIndex[1] = tmp.y;
	//			ret.AffectedBoneIndex[2] = tmp.z;
	//			ret.AffectedBoneIndex[3] = tmp.w;
	//		}
	//	}

	//	{
	//		{
	//			auto data = GetUnitElementBinary(str, offset);
	//			std::string elem = data.str;
	//			offset = data.offset;

	//			Float4 tmp;
	//			DeserializeBinary(elem, tmp);
	//			ret.Weight[0] = tmp.x;
	//			ret.Weight[1] = tmp.y;
	//			ret.Weight[2] = tmp.z;
	//			ret.Weight[3] = tmp.w;
	//		}
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, Vertex_PCNTs_Skinning& ret)
	//{
	//	int offset = 1;
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		DeserializeBinary(elem, ret.Position);
	//		offset = data.offset;
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		DeserializeBinary(elem, ret.Color);
	//		offset = data.offset;
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		DeserializeBinary(elem, ret.Normal);
	//		offset = data.offset;
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		DeserializeBinary(elem, ret.TextureUV);
	//		offset = data.offset;
	//	}

	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string elem = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(elem, ret.MaterialIndex);
	//	}

	//	{
	//		{
	//			auto data = GetUnitElementBinary(str, offset);
	//			std::string elem = data.str;
	//			offset = data.offset;

	//			Float4 tmp;
	//			DeserializeBinary(elem, tmp);
	//			ret.AffectedBoneIndex[0] = tmp.x;
	//			ret.AffectedBoneIndex[1] = tmp.y;
	//			ret.AffectedBoneIndex[2] = tmp.z;
	//			ret.AffectedBoneIndex[3] = tmp.w;
	//		}
	//	}

	//	{
	//		{
	//			auto data = GetUnitElementBinary(str, offset);
	//			std::string elem = data.str;
	//			offset = data.offset;

	//			Float4 tmp;
	//			DeserializeBinary(elem, tmp);
	//			ret.Weight[0] = tmp.x;
	//			ret.Weight[1] = tmp.y;
	//			ret.Weight[2] = tmp.z;
	//			ret.Weight[3] = tmp.w;
	//		}
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, MeshData& ret)
	//{
	//	auto data = GetUnitElementBinary(str, 0);
	//	std::string elem = data.str;
	//	DeserializeBinary(elem, ret.MeshIndex);
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, MeshToBoneSpaceTransformData& ret, int maxBoneCount)
	//{
	//	auto data = GetUnitElementBinary(str, 0);
	//	std::string elem = data.str;
	//	int offset = 1;
	//	for (int i = 0; i < maxBoneCount; ++i)
	//	{
	//		auto valData = GetUnitElementBinary(elem, offset);
	//		std::string val = valData.str;
	//		offset = valData.offset;

	//		Float44 tmp;
	//		DeserializeBinary(val, tmp);
	//		ret.BoneSpaceTransformBuffer[i] = {
	//			tmp.e11, tmp.e12, tmp.e13, tmp.e14,
	//			tmp.e21, tmp.e22, tmp.e23, tmp.e24,
	//			tmp.e31, tmp.e32, tmp.e33, tmp.e34,
	//			tmp.e41, tmp.e42, tmp.e43, tmp.e44,
	//		};
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, AnimationUnitInfo& ret)
	//{
	//	auto data = GetUnitElementBinary(str, 0);
	//	std::string elem = data.str;

	//	int offset = 1;
	//	{
	//		auto localElemData = GetUnitElementBinary(elem, offset);
	//		std::string localElem = localElemData.str;
	//		offset = localElemData.offset;
	//		Float44 val;
	//		DeserializeBinary(localElem, val);
	//		ret.Matrix = {
	//			val.e11, val.e12, val.e13, val.e14,
	//			val.e21, val.e22, val.e23, val.e24,
	//			val.e31, val.e32, val.e33, val.e34,
	//			val.e41, val.e42, val.e43, val.e44,
	//		};
	//	}

	//	{
	//		auto localElemData = GetUnitElementBinary(elem, offset);
	//		std::string localElem = localElemData.str;
	//		offset = localElemData.offset;
	//		Float3 val;
	//		DeserializeBinary(localElem, val);
	//		ret.Translate = { val.x, val.y, val.z };
	//	}

	//	{
	//		auto localElemData = GetUnitElementBinary(elem, offset);
	//		std::string localElem = localElemData.str;
	//		offset = localElemData.offset;
	//		Float3 val;
	//		DeserializeBinary(localElem, val);
	//		ret.Scale = { val.x, val.y, val.z };
	//	}

	//	{
	//		auto localElemData = GetUnitElementBinary(elem, offset);
	//		std::string localElem = localElemData.str;
	//		offset = localElemData.offset;
	//		Float4 val;
	//		DeserializeBinary(localElem, val);
	//		ret.Rotate = { val.x, val.y, val.z, val.w };
	//	}
	//}
	//void SerializeableBinary::DeserializeBinary(std::string& str, AnimationFrameInfo& ret, int maxBoneCount, int maxMeshCount)
	//{
	//	str = GetUnitElementBinary(str, 0).str;

	//	int offset = 1;
	//	for (int i = 0; i < maxBoneCount; ++i)
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string val = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(val, ret.BoneAnimationUnit[i]);
	//	}

	//	for (int i = 0; i < maxMeshCount; ++i)
	//	{
	//		auto data = GetUnitElementBinary(str, offset);
	//		std::string val = data.str;
	//		offset = data.offset;
	//		DeserializeBinary(val, ret.MeshAnimationUnit[i]);
	//	}
	//}
}