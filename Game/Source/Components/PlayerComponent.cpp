#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent);

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void PlayerComponent::Update(float dt)
{
	bool onGround = groundCount > 0;

	float xDir = 0;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) xDir -= 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) xDir += 1;

	float modifier = (onGround) ? 1 : 0.45f;
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

	if (owner->transform.position.x < -32 || owner->transform.position.x > 1232 || owner->transform.position.y > 832)
	{
		std::cout << "Player Off Screen\n";
		owner->isDestroyed = true;
		EVENT_NOTIFY(PlayerDead);
	}
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	if (IsEqualIgnoreCase(actor->tag, "ground")) groundCount++;
	if (IsEqualIgnoreCase(actor->tag, "enemy"))
	{
		owner->isDestroyed = true;
		EVENT_NOTIFY(PlayerDead);
	}
	if (IsEqualIgnoreCase(actor->tag, "pickup"))
	{
		if (IsEqualIgnoreCase(actor->name, "coin") && !actor->isDestroyed) EVENT_NOTIFY_DATA(AddPoints, 100);
		actor->isDestroyed = true;
	}
	if (IsEqualIgnoreCase(actor->tag, "goal"))
	{
		actor->Deactivate();
		EVENT_NOTIFY(LevelComplete);
	}
}

void PlayerComponent::OnCollisionExit(Actor* actor)
{
	if (IsEqualIgnoreCase(actor->tag, "ground")) groundCount--;
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