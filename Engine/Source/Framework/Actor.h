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
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }

	void SetTransform(const Transform& transform) { m_transform = transform; }
	const Transform& GetTransform() { return m_transform; }

	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	virtual void OnCollision(Actor* actor) {};
	float GetRadius() { return 0; }

	virtual void SetHP(int hp) { m_hp = hp; }

	void SetDamage(int damage) { m_damage = damage; }
	int GetDamage() const { return m_damage; }

	friend class Scene;

protected:
	std::string m_tag;
	int m_hp = 0;
	bool m_destroyed = false;
	float m_lifespan = -1;

	Transform m_transform{ {0, 0} };
	Vector2 m_velocity{ 0, 0 };
	float m_damping = 0;

	int m_damage = 0;

	Scene* m_scene{ nullptr };

	std::vector<std::unique_ptr<Component>> m_components;
};