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
}