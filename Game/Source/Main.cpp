#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("Text.txt", s);
	std::cout << s << std::endl;

	rapidjson::Document document;
	Json::Load("Text.txt", document);

	std::string name;
	int age;
	bool isAwake;

	
	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, isAwake);
	std::cout << name << std::endl << age << std::endl << isAwake << std::endl;

	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("TestImage.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("pdark.ttf", 30);

		std::unique_ptr<Text> text = std::make_unique<Text>(font, true);
		text->Create(engine->GetRenderer(), "Hello World!", { 1, 1, 1 });

		std::unique_ptr<Actor> actor = std::make_unique<Actor>(Transform{ { 400, 300 } });
		std::unique_ptr<TextureComponent> tc = std::make_unique<TextureComponent>();
		tc->texture = texture;
		actor->AddComponent(std::move(tc));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 400, 300);
			engine->GetRenderer().DrawTexture(texture.get(), 0, 0);

			engine->GetPS().Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}