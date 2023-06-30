#include <Windows/Engine.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR ipCmdLine, int nCmdShow)
{
	/*Result result;
	ConstantBuffer cb;
	HLSL::Layout layout;
	layout["my_bool"] = true;
	layout["my_float"] = (float)0xffffff;
	layout["my_integer"] = (int)0xffffff;
	layout["my_struct"] = HLSL::Struct({
		0xffffff,
		0xffffff,
		0xffffff
		});
	cb.Init(layout);
	cb["my_struct"] = HLSL::Struct({
		0xffffff, 0xffffff, 0xffffff
		});
	
	std::string out;
	out += "my_bool: " + std::to_string(cb["my_bool"].GetOffset());
	out += "\nmy_float: " + std::to_string(cb["my_float"].GetOffset());
	out += "\nmy_integer: " + std::to_string(cb["my_integer"].GetOffset());
	out += "\nmy_struct: " + std::to_string(cb["my_struct"].GetOffset());
	out += "\n1: " + std::to_string(cb["my_struct"][HLSL::Index(0)].GetOffset());
	out += "\n2: " + std::to_string(cb["my_struct"][HLSL::Index(1)].GetOffset());
	out += "\n3: " + std::to_string(cb["my_struct"][HLSL::Index(2)].GetOffset());
	*/

	Duat::Engine engine("Duat");
	engine.StartUp();
	engine.Run();
	engine.ShutDown();

	return 0;
} 