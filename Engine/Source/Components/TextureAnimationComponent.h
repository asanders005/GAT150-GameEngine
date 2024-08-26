#pragma once
#include "TextureComponent.h"
#include "Renderer\Texture.h"

class TextureAnimationComponent : public TextureComponent
{
public:
	CLASS_DECLARATION(TextureAnimationComponent)
	CLASS_PROTOTYPE(TextureAnimationComponent)

	void Initialize() override;
	void Update(float dt) override;

public:
	float fps = 0;
	bool loop = true;

	int numColumns = 0;
	int numRows = 0;
	int startFrame = 0;
	int endFrame = 0;

	int frame = 0;
	float frameTimer = 0;
};