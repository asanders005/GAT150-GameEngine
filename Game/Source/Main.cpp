#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("TestImage.jpg", engine->GetRenderer());
	res_t<Font> font = ResourceManager::Instance().Get<Font>("pdark.ttf", 30);

	std::unique_ptr<Text> text = std::make_unique<Text>(font, true);
	text->Create(engine->GetRenderer(), "Hello World!", { 1, 1, 1 });

	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		text->Draw(engine->GetRenderer(), 400, 300);
		engine->GetRenderer().DrawTexture(texture.get(), 0, 0);

		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	text->~Text();
	font->~Font();

	engine->Shutdown();

	return 0;
}