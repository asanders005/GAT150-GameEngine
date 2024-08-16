#pragma once
#include "Object.h"
#include <list>
#include <string>
#include <memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object
{
public:
	Scene(Engine* engine, Game* game = nullptr) : engine{ engine }, game { game } {}

	void Initialize() override;

	CLASS_DECLARATION(Scene);

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	

	void RemoveAll();
	void RemoveAll(std::string tag);

	template<typename T>
	T* GetActor();

	template<typename T>
	T* GetActor(const std::string& name);

public:
	Engine* engine;
	Game* game;
	
private:
	std::list<std::unique_ptr<Actor>> actors;
};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline T* Scene::GetActor(const std::string& name)
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result && IsEqualIgnoreCase(result->name, name)) return result;
	}

	return nullptr;
}
