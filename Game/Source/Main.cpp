#include "Engine.h"

#include <iostream>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		PS.Draw(RENDERER);

		RENDERER.EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}