#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent);

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt)
{
	bool onGround = groundCount > 0;

	float xDir = 0;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) xDir -= 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) xDir += 1;

	float modifier = (onGround) ? 1 : 0.8f;
	physics->ApplyForce(Vector2{ xDir, 0.0f } * speed * modifier);
	if (xDir != 0) 
	{
		animation->SetAnimation("walk");
		animation->hflip = (xDir < 0) ? true : false;
	}
	else animation->SetAnimation("idle");

	if (owner->scene->engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && onGround)
	{
		physics->SetVelocity(Vector2{ physics->velocity.x, -1.0f * jumpSpeed });
	}
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	if (IsEqualIgnoreCase(actor->tag, "ground")) groundCount++;
	if (IsEqualIgnoreCase(actor->tag, "enemy")) EVENT_NOTIFY(PlayerDead);
	if (IsEqualIgnoreCase(actor->tag, "pickup"))
	{
		if (IsEqualIgnoreCase(actor->name, "coin")) EVENT_NOTIFY_DATA(AddPoints, 100);
		actor->isDestroyed = true;
	}
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (IsEqualIgnoreCase(actor->tag, "ground")) groundCount--;
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