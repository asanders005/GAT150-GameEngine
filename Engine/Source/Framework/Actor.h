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
	CLASS_DECLARATION(Actor)

	Actor() = default;
	Actor(const Transform& transform) : m_transform{transform} {}

	void Initialize() override;

	virtual void Update(float dt);
	virtual void Draw(class Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	void SetDamping(float damping) { m_damping = damping; }

	void SetTransform(const Transform& transform) { m_transform = transform; }
	const Transform& GetTransform() { return m_transform; }

	virtual void OnCollision(Actor* actor) {};
	float GetRadius() { return 0; }

	virtual void SetHP(int hp) { m_hp = hp; }

	friend class Scene;

public:
	std::string tag;
	float lifespan = -1;

protected:
	int m_hp = 0;
	bool m_destroyed = false;

	Transform m_transform{ {0, 0} };
	Vector2 m_velocity{ 0, 0 };
	float m_damping = 0;

	int m_damage = 0;

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
};