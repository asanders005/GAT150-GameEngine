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
class creator : public CreatorBase
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


private:
	std::map<std::string, std::unique_ptr<class Object>> m_registry;
};