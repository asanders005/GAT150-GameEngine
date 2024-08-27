#include "FungalLeap.h"
#include "Engine.h"
#include <functional>

bool FungalLeap::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	rapidjson::Document document;
	Json::Load(sceneNames[0], document);
	Json::Load(tilemapNames[0], document);
	m_scene->Read(document);

	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, FungalLeap::OnPlayerDead);
	ADD_OBSERVER(AddPoints, FungalLeap::OnAddPoints);

    return true;
}

void FungalLeap::Shutdown()
{
	m_scene->RemoveAll();
}

void FungalLeap::Update(float dt)
{
	m_scene->Update(dt);
}

void FungalLeap::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

bool FungalLeap::LoadScene(int i)
{
	m_scene->RemoveAll();

	rapidjson::Document document;
	Json::Load(sceneNames[i], document);
	Json::Load(tilemapNames[i], document);
	m_scene->Read(document);

	m_scene->Initialize();

	return true;
}

void FungalLeap::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead\n";
}

void FungalLeap::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
