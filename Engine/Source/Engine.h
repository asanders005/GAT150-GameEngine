#pragma once
#include "Audio.h"
#include "Input.h"
#include "Renderer.h"

#include "ETime.h"

#include "Mathutils.h"
#include "Random.h"
#include "Vector2.h"

#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Transform.h"

#include <fmod.h>
#include <SDL.h>
#include <memory>

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }
	void SetParticlesActive(bool active) { m_particlesActive = active; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;

	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	bool m_particlesActive = true;
	std::unique_ptr<ParticleSystem> m_particleSystem;
};