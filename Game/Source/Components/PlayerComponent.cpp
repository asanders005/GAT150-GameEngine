#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	float xDir = 0;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) xDir -= 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) xDir += 1;
	owner->GetComponent<PhysicsComponent>()->ApplyForce(Vector2{ xDir, 0.0f } * speed);

	if (owner->scene->engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		owner->GetComponent<PhysicsComponent>()->ApplyForce(Vector2{ 0, -1 } * jumpSpeed * 10);
	}

	/*if (owner->scene->engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		auto rocket = Factory::Instance().Create<Actor>("rocket");

		rocket->transform.position = owner->transform.position;
		rocket->transform.rotation = owner->transform.rotation - 90;

		owner->scene->AddActor(std::move(rocket), true);
	}*/
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "ground")
	{
		// owner->GetComponent<PhysicsComponent>()->
	}
	if (actor->tag == "mushroom")
	{
		
	}
	if (actor->tag == "enemy") EVENT_NOTIFY(PlayerDead);
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
	READ_DATA(value, jumpSpeed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}