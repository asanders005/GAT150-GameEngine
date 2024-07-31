#pragma once
#include <string>
#include <filesystem>

namespace File
{
	std::string GetFilePath();
	bool SetFilePath(std::string filepath);
}