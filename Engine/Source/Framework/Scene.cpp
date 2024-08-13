#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}

void Scene::Update(float dt)
{
	for (auto& actor : actors)
	{
		actor->Update(dt);
	}
	
	std::erase_if(actors, [](auto& actor) { return actor->isDestroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	actors.clear();
}

void Scene::RemoveAll(std::string tag)
{
	actors.erase(std::remove_if(actors.begin(), actors.end(), [&](auto& actor) { return actor->tag == tag; }), actors.end());
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{

}
