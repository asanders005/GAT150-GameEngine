#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent);

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);
}

void CharacterComponent::Update(float dt)
{
	float xDir = 0;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) xDir -= 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) xDir += 1;
	if (xDir != 0) 
	{
		/*animations["idleAnim"]->Deactivate();
		animations["walkAnim"]->Activate();*/
	}
	else
	{
		/*animations["walkAnim"]->Deactivate();
		animations["idleAnim"]->Activate();*/
	}
	owner->GetComponent<PhysicsComponent>()->ApplyForce(Vector2{ xDir, 0.0f } * speed * 50);

	if (owner->scene->engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && onGround)
	{
		owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{ 0, -1 } * jumpSpeed);
	}
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "Ground")
	{
		onGround = true;
	}
	if (actor->tag == "enemy") EVENT_NOTIFY(PlayerDead);
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "Ground")
	{
		onGround = false;
	}
}

void CharacterComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
	READ_DATA(value, jumpSpeed);
}

void CharacterComponent::Write(json_t& value)
{
	//
}