#pragma once
#include "Math/Vector2.h"
#include "Renderer/Color.h"
#include <string>
#include <rapidjson/document.h>

#define READ_DATA(value, data) Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)

namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired = false);
}

using json_t = rapidjson::Value;