#include "FungalLeap.h"
#include "Engine.h"
#include <functional>

bool FungalLeap::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	rapidjson::Document document;
	Json::Load("Scenes/Initialize.json", document);
	m_scene->Read(document);
	Json::Load("Scenes/title.json", document);
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
	switch (m_state)
	{
	case eState::TITLE:
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_state = eState::GAME_START;
		}
		break;
	case eState::GAME_START:
		m_level = 0;
		m_lives = 3;

		LoadScene(0);
		m_state = eState::GAME;
		break;
	case eState::LEVEL_START:
		LoadScene(m_level);
		m_state = eState::GAME;
		break;
	case eState::GAME:
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			m_state = eState::PAUSE;
		}
		break;
	case eState::PAUSE:
		break;
	case eState::PLAYER_DEAD:
		m_deathTimer -= dt;
		if (m_deathTimer <= 0)
		{
			m_state = (m_lives < 0) ? eState::GAME_OVER : eState::LEVEL_START;
		}
		break;
	case eState::GAME_OVER:
		m_scene->RemoveAll();

		rapidjson::Document document;
		Json::Load("Scenes/title.json", document);
		m_scene->Read(document);

		m_scene->Initialize();
		m_state = eState::TITLE;
		break;
	}
	
	if (m_state != eState::PAUSE) m_scene->Update(dt);
}

void FungalLeap::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

bool FungalLeap::LoadScene(int i)
{
	m_scene->RemoveAll();

	rapidjson::Document document;
	Json::Load(tilemapNames[i], document);
	m_scene->Read(document);
	Json::Load(sceneNames[i], document);
	m_scene->Read(document);

	m_scene->Initialize();

	m_spawnpoint = m_scene->GetActor<Actor>("spawn");
	auto player = Factory::Instance().Create<Actor>("player");

	if (m_spawnpoint) player->transform.position = m_spawnpoint->transform.position;
	else player->transform.position = { 16, 16 };

	m_scene->AddActor(std::move(player), true);

	return true;
}

void FungalLeap::OnPlayerDead(const Event& event)
{
	m_lives--;
	m_deathTimer = 3;
	m_state = eState::PLAYER_DEAD;
}

void FungalLeap::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
