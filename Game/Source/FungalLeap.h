#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class FungalLeap : public Game, Observer
{
public:
	enum class eState
	{
		TITLE,
		GAME_START,
		LEVEL_START,
		GAME,
		PAUSE,
		PLAYER_DEAD,
		GAME_OVER
	};
public:
	FungalLeap(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	bool LoadScene(int i);

	// events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);
	void OnLevelComplete(const Event& event);

private:
	eState m_state{ eState::TITLE };
	int m_level = 0;

	std::unique_ptr<class Scene> m_scene;
	class Actor* m_spawnpoint{ nullptr };
	class Actor* m_audioController{ nullptr };
	std::unique_ptr<class Actor> m_pauseText;

	float m_deathTimer = 0;

	std::string tilemapNames[5]
	{ 
		"Scenes/prototypeTilemap.json", 
		"Scenes/Level1.json", 
		"Scenes/Level2.json",
		"Scenes/Level3.json",
		"Scenes/GameWin.json"
	};
};