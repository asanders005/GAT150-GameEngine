#include "EFile.h"

std::string File::GetFilePath()
{
	return std::filesystem::current_path().string();
}

bool File::SetFilePath(std::string filepath)
{
	std::error_code ec;
	std::filesystem::current_path(filepath, ec);

	return !ec;
}
