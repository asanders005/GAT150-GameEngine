#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)

void EnemyComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void EnemyComponent::Update(float dt)
{
	physics->SetVelocity(Vector2{ xDir, 0 } * speed);
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "enemyController")
	{
		xDir = -xDir;
		animation->hflip = !animation->hflip;
	}
}

void EnemyComponent::OnCollisionExit(Actor* actor)
{
	//
}

void EnemyComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
	//
}