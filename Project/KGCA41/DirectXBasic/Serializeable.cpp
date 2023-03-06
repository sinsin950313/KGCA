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
	std::string Serializeable::Serialize(int tabCount, Float4 data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{";
		ret += std::to_string(data.x);
		ret += ", ";
		ret += std::to_string(data.y);
		ret += ", ";
		ret += std::to_string(data.z);
		ret += ", ";
		ret += std::to_string(data.w);
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
		ret += "{";
		ret += std::to_string(data.AffectedBoneIndex[0]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[1]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[2]);
		ret += ", ";
		ret += std::to_string(data.AffectedBoneIndex[3]);
		ret += "}\n";
		ret += GetTabbedString(tabCount + 1);
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
		ret += "{";
		ret += std::to_string(data.MaterialIndex);
		ret += "}\n";
		ret += GetTabbedString(tabCount + 1);
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
		ret += GetTabbedString(tabCount + 1);
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

		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			ret += Serialize(tabCount + 1, (Float44)data.BoneSpaceTransformBuffer[i]);
			ret += GetTabbedString(tabCount + 1);
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
	std::string Serializeable::Serialize(int tabCount, AnimationFrameInfo& data)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "{\n";

		for (int i = 0; i < 255; ++i)
		{
			ret += Serialize(tabCount + 1, data.BoneAnimationUnit[i]);
			ret += GetTabbedString(tabCount + 1);

			if (i + 1 < 255)
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

		for (int i = 0; i < 255; ++i)
		{
			ret += Serialize(tabCount + 1, data.MeshAnimationUnit[i]);
		ret += GetTabbedString(tabCount + 1);

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
	void Serializeable::Deserialize(std::string element, float& ret)
	{
		std::string str = std::string(element.begin() + 1, element.end() - 1);
		ret = std::stof(str);
	}
	void Serializeable::Deserialize(std::string element, Float2& ret)
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
	void Serializeable::Deserialize(std::string element, Float3& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}
		++index;

		for (int i = 0; i < 3; ++i)
		{
			int start = index;

			std::string tmp;
			int count = 0;
			while (element[index] != ',')
			{
				++count;
				++index;
			}
			ret.e[i] = std::stof(std::string(element.begin() + start, element.begin() + start + count));
			++index;
			++index;
		}
	}
	void Serializeable::Deserialize(std::string element, Float33& ret)
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
	void Serializeable::Deserialize(std::string element, Float44& ret)
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
	void Serializeable::Deserialize(std::string element, Vertex_PC& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		{
			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Position);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Color);
		}
	}
	void Serializeable::Deserialize(std::string element, Vertex_PCNT& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		{
			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Position);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Color);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Normal);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.TextureUV);
		}
	}
	void Serializeable::Deserialize(std::string element, Vertex_PCNTs& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		{
			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Position);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Color);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Normal);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.TextureUV);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.MaterialIndex);
		}
	}
	void Serializeable::Deserialize(std::string element, Vertex_PCNT_Skinning& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		{
			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Position);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Color);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Normal);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.TextureUV);
		}

		while (element[index] != '{')
		{
			++index;
		}
		++index;

		for(int i = 0; i < 4; ++i)
		{
			int start = index;
			int count = 0;
			while (element[index] != ',' && element[index] != '}')
			{
				++index;
				++count;
			}
			++index;

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.AffectedBoneIndex[i]);
		}

		while (element[index] != '{')
		{
			++index;
		}
		++index;

		for(int i = 0; i < 4; ++i)
		{
			int start = index;
			int count = 0;
			while (element[index] != ',' && element[index] != '}')
			{
				++index;
				++count;
			}
			++index;

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Weight[i]);
		}
	}
	void Serializeable::Deserialize(std::string element, Vertex_PCNTs_Skinning& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		{
			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Position);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Color);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Normal);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.TextureUV);
		}

		while (element[index] != '{')
		{
			++index;
		}
		++index;

		for(int i = 0; i < 4; ++i)
		{
			int start = index;
			int count = 0;
			while (element[index] != ',' && element[index] != '}')
			{
				++index;
				++count;
			}
			++index;

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.AffectedBoneIndex[i]);
		}

		while (element[index] != '{')
		{
			++index;
		}
		++index;

		for(int i = 0; i < 4; ++i)
		{
			int start = index;
			int count = 0;
			while (element[index] != ',' && element[index] != '}')
			{
				++index;
				++count;
			}
			++index;

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.Weight[i]);
		}

		{
			while (element[index] != '{')
			{
				++index;
			}

			int start = index;
			int count = 0;
			while (element[index] != '}')
			{
				++index;
				++count;
			}

			Deserialize(std::string(element.begin() + start, element.begin() + start + count), ret.MaterialIndex);
		}
	}
	void Serializeable::Deserialize(std::string element, MeshData& ret)
	{
		int start = element.find('{') + 1;
		int end = element.find('}');
		Deserialize(std::string(element.begin() + start, element.begin() + end), ret.MeshIndex);
	}
	void Serializeable::Deserialize(std::string element, MeshToBoneSpaceTransformData& ret)
	{
		int index = 0;
		while (element[index] != '{')
		{
			++index;
		}

		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			while (element[index] != '{')
			{
				++index;
			}
			int start = index;
			int end = element.find('}', index);

			Float44 tmp;
			Deserialize(std::string(element.begin() + index, element.begin() + end), tmp);
			ret.BoneSpaceTransformBuffer[i] = {
				tmp.e11, tmp.e12, tmp.e13, tmp.e14,
				tmp.e21, tmp.e22, tmp.e23, tmp.e24,
				tmp.e31, tmp.e32, tmp.e33, tmp.e34,
				tmp.e41, tmp.e42, tmp.e43, tmp.e44,
			};
		}
	}
	void Serializeable::Deserialize(std::string element, AnimationUnitInfo& ret)
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
	void Serializeable::Deserialize(std::string element, AnimationFrameInfo& ret)
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