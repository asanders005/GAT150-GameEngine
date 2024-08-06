#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

class TextureComponent : public RenderComponent
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

public:
	res_t<Texture> texture;
};