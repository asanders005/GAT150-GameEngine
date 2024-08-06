#pragma once
// ** core **
#include "Core/ETime.h"
#include "Core/EAssert.h"
#include "Core/EFile.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
//input
#include "Input/Input.h"
//audio
#include "Audio/Audio.h"

// ** framework **
#include "Framework/Actor.h"

// ** math **
#include "Math/Mathutils.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Transform.h"

// ** resources **
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// ** components **
#include "Components/TextureComponent.h"

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