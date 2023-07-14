#include <Windows/Engine.h>

using namespace Duat::Utility;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR ipCmdLine, int nCmdShow)
{
	/*/static int x = 12;
	static int y = 6;
	HLSL::Layout layout;
	HLSL::Layout signature;
	signature["param1"] = &x;
	signature["param2"] = &y;
	layout["myFunction"] = HLSL::Function(
		signature,
		[](HLSL::Buffer& input) -> int
		{
			int* a  = (int*)input["param1"];
			int* b  = (int*)input["param2"];
			return *a + *b;
		}
	);*/
	

	Duat::Engine engine("Duat");
	engine.StartUp();
	engine.Run();
	engine.ShutDown();

	return 0;
} 