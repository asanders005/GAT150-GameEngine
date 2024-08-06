#pragma once
#include <string>

class Object
{
public:
	Object() = default;
	Object(const std::string& name) : name{ name } {}

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public:
	std::string name;
	bool active{ false };
};