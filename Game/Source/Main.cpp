#include "Engine.h"
#include "FungalLeap.h"

#include <iostream>

int main(int argc, char* argv[])
{
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	std::unique_ptr<Game> game = std::make_unique<FungalLeap>(engine.get());
	game->Initialize();

	while (!engine->IsQuit())
	{
		// update
		engine->Update();
		game->Update(engine->GetTime().GetDeltaTime());

		// render
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		game->Draw(engine->GetRenderer());

		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}