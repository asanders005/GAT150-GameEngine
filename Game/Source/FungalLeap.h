#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class FungalLeap : public Game, Observer
{
public:
	enum eState
	{
		TITLE,
		GAME_START,
		LOAD_LEVEL,
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

private:
	std::unique_ptr<class Scene> m_scene;

	std::string sceneNames[1] = { "Scenes/scene.json" };
	std::string tilemapNames[1] = { "Scenes/tilemap.json" };
};