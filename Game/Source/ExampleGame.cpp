#include "ExampleGame.h"
#include "Engine.h"
#include <functional>

bool ExampleGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/scene.json" };
	for (auto sceneName : sceneNames)
	{
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}

	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, ExampleGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, ExampleGame::OnAddPoints);

    return false;
}

void ExampleGame::Shutdown()
{
	m_scene->RemoveAll();
}

void ExampleGame::Update(float dt)
{
	m_scene->Update(dt);
}

void ExampleGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void ExampleGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead\n";
}

void ExampleGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
