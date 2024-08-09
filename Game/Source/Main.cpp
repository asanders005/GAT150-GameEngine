#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	//auto a = Factory::Instance().Create("Actor");

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
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	
	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);
	std::cout << name << std::endl;
	std::cout << age << std::endl;
	std::cout << speed << std::endl;
	std::cout << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;

	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("TestImage.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("pdark.ttf", 30);

		std::unique_ptr<Text> text = std::make_unique<Text>(font, true);
		text->Create(engine->GetRenderer(), "Hello World!", { 1, 1, 1 });

		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform({ { 400, 300 } });
		auto tc = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
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