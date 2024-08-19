#include "Engine.h"
#include "Components/PlayerComponent.h"
#include <iostream>

void f1(int i) { std::cout << "f1: " << i << std::endl; }
void f2(int i) { std::cout << "f2: " << i << std::endl; }

int main(int argc, char* argv[])
{
	void(*fp)(int);
	fp = &f1;
	fp(66);
	fp = &f2;
	fp(-21);

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// !! not necessary code, just shows content of file !!
	/*std::string buffer;
	File::ReadFile("Scenes/scene.json", buffer);
	std::cout << buffer << std::endl;*/

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();
	{
		/*res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("TestImage.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("pdark.ttf", 30);

		std::unique_ptr<Text> text = std::make_unique<Text>(font, true);
		text->Create(engine->GetRenderer(), "Hello World!", { 1, 1, 1 });

		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->transform = { { 400, 300 } };
		auto tc = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		tc->texture = texture;
		actor->AddComponent(std::move(tc));*/

		while (!engine->IsQuit())
		{
			// update
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto* actor = scene->GetActor<Actor>("text");
			//if (actor)
			//{
			//	//actor->transform.position.x += 50 * engine->GetTime().GetDeltaTime();
			//	actor->transform.rotation += 720 * engine->GetTime().GetDeltaTime();
			//	actor->transform.scale = 2 * Math::Abs(Math::Sin(engine->GetTime().GetTime()));
			//}

			// render
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetPS().Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}