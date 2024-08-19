#pragma once
#include "Core/ISerializable.h"
#include "Core/Factory.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	static const char* GetTypeName() { return #classname; } \
	virtual void Read(const json_t& value); \
	virtual void Write(json_t& value);

#define FACTORY_REGISTER(classname) \
	class Register##classname \
	{ \
	public: \
		Register##classname() \
		{ \
			Factory::Instance().Register<classname>(#classname); \
		} \
	}; \
	static Register##classname register_instance;


class Object : public Serializable
{
public:
	Object() = default;
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	CLASS_DECLARATION(Object);

	virtual void Initialize() = 0;
	virtual void Activate() { isActive = true; }
	virtual void Deactivate() { isActive = false; }

public:
	std::string name;
	bool isActive = true;
};