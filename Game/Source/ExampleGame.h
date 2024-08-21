#pragma once
#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class ExampleGame : public Game, Observer
{
public:
	ExampleGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	// events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);

private:
	std::unique_ptr<class Scene> m_scene;
};