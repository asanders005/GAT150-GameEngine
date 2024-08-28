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

	/*m_pauseText = Factory::Instance().Create<Actor>("pauseText");
	m_pauseText->Initialize();*/

	ADD_OBSERVER(PlayerDead, FungalLeap::OnPlayerDead);
	ADD_OBSERVER(AddPoints, FungalLeap::OnAddPoints);
	ADD_OBSERVER(LevelComplete, FungalLeap::OnLevelComplete);

    return true;
}

void FungalLeap::Shutdown()
{
	m_scene->RemoveAll(true);
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
		m_level = 1;
		m_lives = 3;

		m_scene->GetActor("lifeHead")->Activate();

		m_state = eState::LEVEL_START;
		break;
	case eState::LEVEL_START:
		LoadScene(m_level);
		break;
	case eState::GAME:
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			m_scene->GetActor("pauseText")->Activate();
			m_state = eState::PAUSE;
		}
		break;
	case eState::PAUSE:
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			m_scene->GetActor("pauseText")->Deactivate();
			m_state = eState::GAME;
		}
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

	if (m_state == eState::PAUSE)
	{
		m_engine->GetRenderer().SetColor(Color{ 0.0f, 0.0f, 0.0f, 0.5f });
		m_engine->GetRenderer().DrawRect(600, 400, 1200, 800);
	}
}

bool FungalLeap::LoadScene(int i)
{
	m_scene->RemoveAll();

	rapidjson::Document document;
	if (Json::Load(tilemapNames[i], document)) m_scene->Read(document);
	if (Json::Load(sceneNames[i], document)) m_scene->Read(document);

	m_scene->Initialize();

	std::vector<Actor*> enemySpawns = m_scene->GetActors("enemySpawn");

	for (auto spawn : enemySpawns)
	{
		auto enemy = Factory::Instance().Create<Actor>("enemy");
		enemy->transform.position = spawn->transform.position;

		m_scene->AddActor(std::move(enemy), true);
	}

	m_spawnpoint = m_scene->GetActor("spawn");
	auto player = Factory::Instance().Create<Actor>("player");

	if (m_spawnpoint) player->transform.position = m_spawnpoint->transform.position;
	else player->transform.position = { 16, 16 };

	m_scene->AddActor(std::move(player), true);

	m_state = eState::GAME;

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

void FungalLeap::OnLevelComplete(const Event& event)
{
	m_score += 1000;
	std::cout << "Level Complete\n";
	m_level++;
	m_state = eState::LEVEL_START;
}
