#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <vector>
#include <memory>

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

	void AddComponent(std::unique_ptr<Component> component);

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