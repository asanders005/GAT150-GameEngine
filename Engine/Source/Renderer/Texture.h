#pragma once
#include "Resources/Resource.h"
#include <string>

struct Vector2;

class Texture : public Resource
{
public:
	Texture() = default;
	~Texture();

	bool Create(std::string name, ...) override;

	Vector2 GetSize();

	friend class Renderer;

private:
	struct SDL_Texture* m_texture{ nullptr };

	bool Load(const std::string& filename, class Renderer& renderer);
};