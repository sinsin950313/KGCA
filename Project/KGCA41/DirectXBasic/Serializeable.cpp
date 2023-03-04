#include "Serializeable.h"
#include <regex>

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
	std::string Serializeable::Serialize(int tabCount, float data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{";
		ret += std::to_string(data);
		ret += "}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float2 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{";
		ret += std::to_string(data.x);
		ret += ", ";
		ret += std::to_string(data.y);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float3 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{";
		ret += std::to_string(data.x);
		ret += ", ";
		ret += std::to_string(data.y);
		ret += ", ";
		ret += std::to_string(data.z);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float33 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e11);
		ret += ", ";
		ret += std::to_string(data.e12);
		ret += ", ";
		ret += std::to_string(data.e13);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e21);
		ret += ", ";
		ret += std::to_string(data.e22);
		ret += ", ";
		ret += std::to_string(data.e23);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e31);
		ret += ", ";
		ret += std::to_string(data.e32);
		ret += ", ";
		ret += std::to_string(data.e33);
		ret += ",\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, Float44 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e11);
		ret += ", ";
		ret += std::to_string(data.e12);
		ret += ", ";
		ret += std::to_string(data.e13);
		ret += ", ";
		ret += std::to_string(data.e14);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e21);
		ret += ", ";
		ret += std::to_string(data.e22);
		ret += ", ";
		ret += std::to_string(data.e23);
		ret += ", ";
		ret += std::to_string(data.e24);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e31);
		ret += ", ";
		ret += std::to_string(data.e32);
		ret += ", ";
		ret += std::to_string(data.e33);
		ret += ", ";
		ret += std::to_string(data.e34);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += std::to_string(data.e41);
		ret += ", ";
		ret += std::to_string(data.e42);
		ret += ", ";
		ret += std::to_string(data.e43);
		ret += ", ";
		ret += std::to_string(data.e44);
		ret += "\n";

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
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
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
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
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
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "}\n";
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{";
		ret += std::to_string(data.Weight[0]);
		ret += ", ";
		ret += std::to_string(data.Weight[1]);
		ret += ", ";
		ret += std::to_string(data.Weight[2]);
		ret += ", ";
		ret += std::to_string(data.Weight[3]);
		ret += "}\n";

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
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Color);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Normal);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.TextureUV);
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{";
		ret += std::to_string(data.MaterialIndex);
		ret += "}";
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "}\n";
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "{";
		ret += std::to_string(data.Weight[0]);
		ret += ", ";
		ret += std::to_string(data.Weight[1]);
		ret += ", ";
		ret += std::to_string(data.Weight[2]);
		ret += ", ";
		ret += std::to_string(data.Weight[3]);
		ret += "}\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, MeshData data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{";
		ret += std::to_string(data.MeshIndex);
		ret += "}";
		ret += "\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, MeshToBoneSpaceTransformData& data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		for (int i = 0; i < 255; ++i)
		{
			ret += Serialize(tabCount + 1, (Float44)data.BoneSpaceTransformBuffer[i]);
			if (i + 1 < 255)
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
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Translate);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Scale);
		ret += ",\n";

		ret += Serialize(tabCount + 1, data.Rotate);
		ret += "\n";

		ret += GetTabbedString(tabCount);
		ret += "}\n";

		return ret;
	}
	std::string Serializeable::Serialize(int tabCount, AnimationFrameInfo& data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		for (int i = 0; i < 255; ++i)
		{
			ret += Serialize(tabCount + 1, data.BoneAnimationUnit[i]);

			if (i + 1 < 255)
			{
				ret += ",\n";
			}
			else
			{
				ret += "\n";
			}
		}
		ret += ",\n";

		for (int i = 0; i < 255; ++i)
		{
			ret += Serialize(tabCount + 1, data.MeshAnimationUnit[i]);

			if (i + 1 < 255)
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
	std::string Serializeable::GetUnitObject(std::string str, int offset)
	{
		int startIndex = 0;
		int endIndex = 0;
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

		return std::string(str.begin() + startIndex, str.begin() + endIndex);
	}
	std::string Serializeable::GetUnitElement(std::string str, int offset)
	{
		int startIndex = 0;
		int endIndex = 0;
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

		return std::string(str.begin() + startIndex, str.begin() + endIndex);
	}
	void Serializeable::DeSerialize(std::string element, float& ret)
	{
		std::string str = std::string(element.begin() + 1, element.end() - 1);
		ret = std::stof(str);
	}
	void Serializeable::DeSerialize(std::string element, Float2& ret)
	{
		int index = 1;
		{
			std::string str;
			while (element[index] != ',')
			{
				str += element[index];
				++index;
			}
			ret.x = std::stof(str);
		}

		// ','
		++index;
		// ' '
		++index;

		{
			std::string str;
			while (element[index] != '\"')
			{
				str += element[index];
				++index;
			}
			ret.y = std::stof(str);
		}
	}
	void Serializeable::DeSerialize(std::string element, Float3& ret)
	{
		int index = 1;
		{
			std::string str;
			while (element[index] != ',')
			{
				str += element[index];
				++index;
			}
			ret.x = std::stof(str);
		}

		// ','
		++index;
		// ' '
		++index;

		{
			std::string str;
			while (element[index] != ',')
			{
				str += element[index];
				++index;
			}
			ret.y = std::stof(str);
		}

		// ','
		++index;
		// ' '
		++index;

		{
			std::string str;
			while (element[index] != '\"')
			{
				str += element[index];
				++index;
			}
			ret.z = std::stof(str);
		}
	}
	void Serializeable::DeSerialize(std::string element, Float33& ret)
	{
		float val[9] = { 0, };
		int valIndex = 0;

		std::string str;
		int index = 1;
		while (element[index] != '\"')
		{
			char c = element[index];
			if (c == '\"')
			{
				break;
			}
			else if (c != ',')
			{
				str += c;
				++index;
			}
			else
			{
				val[valIndex] = std::stof(str);
				++valIndex;
				index += 2;
			}
		}

		ret = {
			val[0], val[1], val[2],
			val[3], val[4], val[5],
			val[6], val[7], val[8]
		};
	}
	void Serializeable::DeSerialize(std::string element, Float44& ret)
	{
		float val[16] = { 0, };
		int valIndex = 0;

		std::string str;
		int index = 1;
		while (element[index] != '\"')
		{
			char c = element[index];
			if (c == '\"')
			{
				break;
			}
			else if (c != ',')
			{
				str += c;
				++index;
			}
			else
			{
				val[valIndex] = std::stof(str);
				++valIndex;
				index += 2;
			}
		}

		ret = {
			val[0], val[1], val[2], val[3],
			val[4], val[5], val[6], val[7],
			val[8], val[9], val[10], val[11],
			val[12], val[13], val[14], val[15]
		};
	}
	void Serializeable::DeSerialize(std::string element, Vertex_PC& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Position.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Color.e[i] = std::stof(match.str());
			element = match.suffix();
		}
	}
	void Serializeable::DeSerialize(std::string element, Vertex_PCNT& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Position.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Color.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Normal.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 2; ++i)
		{
			std::regex_search(element, match, re);
			ret.TextureUV.e[i] = std::stof(match.str());
			element = match.suffix();
		}
	}
	void Serializeable::DeSerialize(std::string element, Vertex_PCNTs& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Position.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Color.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Normal.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 2; ++i)
		{
			std::regex_search(element, match, re);
			ret.TextureUV.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		re = "[0-9]+";
		std::regex_search(element, match, re);
		ret.MaterialIndex = std::stof(match.str());
	}
	void Serializeable::DeSerialize(std::string element, Vertex_PCNT_Skinning& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Position.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Color.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Normal.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 2; ++i)
		{
			std::regex_search(element, match, re);
			ret.TextureUV.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		re = "[0-9]+";
		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.AffectedBoneIndex[i] = std::stoi(match.str());
			element = match.suffix();
		}

		re = "[0-9.e+-]+";
		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Weight[i] = std::stof(match.str());
			element = match.suffix();
		}
	}
	void Serializeable::DeSerialize(std::string element, Vertex_PCNTs_Skinning& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Position.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Color.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Normal.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		for (int i = 0; i < 2; ++i)
		{
			std::regex_search(element, match, re);
			ret.TextureUV.e[i] = std::stof(match.str());
			element = match.suffix();
		}

		re = "[0-9]+";
		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.AffectedBoneIndex[i] = std::stoi(match.str());
			element = match.suffix();
		}

		re = "[0-9.e+-]+";
		for (int i = 0; i < 4; ++i)
		{
			std::regex_search(element, match, re);
			ret.Weight[i] = std::stof(match.str());
			element = match.suffix();
		}

		re = "[0-9]+";
		std::regex_search(element, match, re);
		ret.MaterialIndex = std::stoi(match.str());
	}
	void Serializeable::DeSerialize(std::string element, MeshData& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		re = "[0-9]+";
		std::regex_search(element, match, re);
		ret.MeshIndex = std::stoi(match.str());
	}
	void Serializeable::DeSerialize(std::string element, MeshToBoneSpaceTransformData& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			float val[16];
			for (int j = 0; j < 16; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float44 result;
			memcpy(&result, val, sizeof(float) * 16);

			{
				HMatrix44 tmp = {
					result.e11, result.e12, result.e13, result.e14,
					result.e21, result.e22, result.e23, result.e24,
					result.e31, result.e32, result.e33, result.e34,
					result.e41, result.e42, result.e43, result.e44,
				};
				ret.BoneSpaceTransformBuffer[i] = tmp;
			}
		}
	}
	void Serializeable::DeSerialize(std::string element, AnimationUnitInfo& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		{
			float val[16];
			for (int j = 0; j < 16; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float44 result;
			memcpy(&result, val, sizeof(float) * 16);

			HMatrix44 tmp = {
				result.e11, result.e12, result.e13, result.e14,
				result.e21, result.e22, result.e23, result.e24,
				result.e31, result.e32, result.e33, result.e34,
				result.e41, result.e42, result.e43, result.e44,
			};
			ret.Matrix = tmp;
		}

		{
			float val[3];
			for (int j = 0; j < 3; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float3 result;
			memcpy(&result, val, sizeof(float) * 3);
			ret.Translate = result;
		}

		{
			float val[3];
			for (int j = 0; j < 3; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float3 result;
			memcpy(&result, val, sizeof(float) * 3);
			ret.Scale = result;
		}

		{
			float val[4];
			for (int j = 0; j < 4; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float4 result;
			memcpy(&result, val, sizeof(float) * 4);
			ret.Rotate = { result.x, result.y, result.z, result.w };
		}
	}
	void Serializeable::DeSerialize(std::string element, AnimationFrameInfo& ret)
	{
		std::regex re("[0-9.e+-]+");
		std::smatch match;

		for (int i = 0; i < kAnimationUnitMaxIndex; ++i)
		{
			float val[16];
			for (int j = 0; j < 16; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float44 result;
			memcpy(&result, val, sizeof(float) * 16);

			HMatrix44 tmp = {
				result.e11, result.e12, result.e13, result.e14,
				result.e21, result.e22, result.e23, result.e24,
				result.e31, result.e32, result.e33, result.e34,
				result.e41, result.e42, result.e43, result.e44,
			};
			ret.BoneAnimationUnit[i].Matrix = tmp;

			{
				float val[3];
				for (int j = 0; j < 3; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float3 result;
				memcpy(&result, val, sizeof(float) * 3);
				ret.BoneAnimationUnit[i].Translate = result;
			}

			{
				float val[3];
				for (int j = 0; j < 3; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float3 result;
				memcpy(&result, val, sizeof(float) * 3);
				ret.BoneAnimationUnit[i].Scale = result;
			}

			{
				float val[4];
				for (int j = 0; j < 4; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float4 result;
				memcpy(&result, val, sizeof(float) * 4);
				ret.BoneAnimationUnit[i].Rotate = { result.x, result.y, result.z, result.w };
			}
		}

		for (int i = 0; i < kAnimationUnitMaxIndex; ++i)
		{
			float val[16];
			for (int j = 0; j < 16; ++j)
			{
				std::regex_search(element, match, re);
				val[j] = std::stof(match.str());
				element = match.suffix();
			}

			Float44 result;
			memcpy(&result, val, sizeof(float) * 16);

			HMatrix44 tmp = {
				result.e11, result.e12, result.e13, result.e14,
				result.e21, result.e22, result.e23, result.e24,
				result.e31, result.e32, result.e33, result.e34,
				result.e41, result.e42, result.e43, result.e44,
			};
			ret.MeshAnimationUnit[i].Matrix = tmp;

			{
				float val[3];
				for (int j = 0; j < 3; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float3 result;
				memcpy(&result, val, sizeof(float) * 3);
				ret.MeshAnimationUnit[i].Translate = result;
			}

			{
				float val[3];
				for (int j = 0; j < 3; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float3 result;
				memcpy(&result, val, sizeof(float) * 3);
				ret.MeshAnimationUnit[i].Scale = result;
			}

			{
				float val[4];
				for (int j = 0; j < 4; ++j)
				{
					std::regex_search(element, match, re);
					val[j] = std::stof(match.str());
					element = match.suffix();
				}

				Float4 result;
				memcpy(&result, val, sizeof(float) * 4);
				ret.MeshAnimationUnit[i].Rotate = { result.x, result.y, result.z, result.w };
			}
		}
	}
}