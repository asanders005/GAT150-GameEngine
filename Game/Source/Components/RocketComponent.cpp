#include "RocketComponent.h"
#include "Engine.h"

FACTORY_REGISTER(RocketComponent);

void RocketComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&RocketComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void RocketComponent::Update(float dt)
{
	if (owner->GetComponent<PhysicsComponent>())
	{	
		owner->GetComponent<PhysicsComponent>()->SetVelocity(owner->transform.Forward() * speed);
	}
}

void RocketComponent::OnCollisionEnter(Actor* actor)
{
	if (!actor->isDestroyed && actor->tag == "enemy")
	{
		actor->isDestroyed = true;
		EVENT_NOTIFY_DATA(AddPoints, 100);
	}
}

void RocketComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void RocketComponent::Write(json_t& value)
{
	//
}