#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <vector>
#include <memory>
#include <functional>

class Scene;

class Actor : public Object
{
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{transform} {}

	CLASS_DECLARATION(Actor);

	void Initialize() override;

	virtual void Update(float dt); 
	virtual void Draw(class Renderer& renderer);

	std::function<void(Actor*)> OnCollisionEnter;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();

	template<typename T>
	std::vector<T*> GetComponents();

	friend class Scene;

public:
	std::string tag;

	float lifespan = -1;
	bool isDestroyed = false;

	Transform transform;
	Scene* scene{ nullptr };

protected:
	std::vector<std::unique_ptr<Component>> components;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;

	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}

	return results;
}
