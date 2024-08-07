#include "json.h"
#include "EFile.h"
#include <iostream>
#include <rapidjson/istreamwrapper.h>

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!File::ReadFile(filename, buffer)) return false;

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		document.ParseStream(istream);
		if (!document.IsObject())
		{
			std::cerr << "Could not parse Json: " << filename << std::endl;
			return false;
		}

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, int& data)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			std::cerr << "Could not read JSON value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			std::cerr << "Could not read JSON value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}

	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			std::cerr << "Could not read JSON value: " << name << std::endl;
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}

}