#pragma once
#include "Components/Component.h"

#include <map>

class EnemyComponent : public Component
{
public:
	CLASS_DECLARATION(CharacterComponent)
	CLASS_PROTOTYPE(CharacterComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);

public:
	float speed = 0;
	float jumpSpeed = 0;

	int groundCount = 0;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};