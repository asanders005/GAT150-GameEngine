#pragma once
#include "Singleton.h"

#include <memory>
#include <map>
#include <string>
#include <iostream>

class CreatorBase
{
public:
	virtual ~CreatorBase() = default;
	virtual std::unique_ptr<class Object> Create() = 0;
};

template <typename T>
class Creator : public CreatorBase
{
public:
	std::unique_ptr<class Object> Create() override
	{
		return std::make_unique<T>();
	}
};

class Factory : public Singleton<Factory>
{
public:
	template<typename T> void Register(const std::string name);
	template<typename T = class Object> std::unique_ptr<T> Create(const std::string name);

private:
	std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
};

template<typename T>
inline void Factory::Register(std::string name)
{
	// add creator of type T to registry
	m_registry[name] = std::make_unique<Creator<T>>();
}

template<typename T>
inline std::unique_ptr<T> Factory::Create(const std::string name)
{
	// check if name is in registry
	if (m_registry.find(name) != m_registry.end())
	{
		// if in registry, create object of type T
		return std::unique_ptr<T>(dynamic_cast<T*>(m_registry[name]->Create().release()));
	}

	// name is not in registry, return empty unique_ptr
	return std::unique_ptr<T>();
}
