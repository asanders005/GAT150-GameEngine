#pragma once
#include "Core/ISerializable.h"
#include <string>

#define CLASS_DECLARATION(class) \
	static const char* GetTypeName() { return #class; } \
	virtual void Read(const json_t& value); \
	virtual void Write(json_t& value);

class Object : public Serializable
{
public:
	Object() = default;
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public:
	std::string name;
	bool active{ false };
};