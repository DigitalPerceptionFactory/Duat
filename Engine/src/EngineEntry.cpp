#include <Windows/Engine.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR ipCmdLine, int nCmdShow)
{
	Duat::Engine engine("Duat");
	engine.StartUp();
	engine.Run();
	engine.ShutDown();

	return 0;
} 