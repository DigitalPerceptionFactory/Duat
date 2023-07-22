#include "Engine.h"


namespace Duat
{
	using namespace DirectX;

	Engine::Engine(std::string title, size_t width, size_t height)
		: m_hInstance(GetModuleHandle(nullptr))
	{
		if (FAILED(CoInitializeEx(0, COINIT_MULTITHREADED)))
			m_result << "Coinitialize failed.";

		int maxWidth = GetSystemMetrics(SM_CXSCREEN);
		int maxHeight = GetSystemMetrics(SM_CYSCREEN);
		if (width == 0) width = maxWidth;
		if (height == 0) height = maxHeight;
		float posX = maxWidth * 0.5f - width * 0.5f;
		float posY = maxHeight * 0.5f - height * 0.5f;

		InitWindow(title, "MainWindow", (LONG)width, (LONG)height, (LONG)posX, (LONG)posY);

		ShowWindow(m_hWnd, SW_SHOW);
	}

	void Engine::StartUp()
	{
		m_gfx.Init(m_hWnd);

		static Geometry::Mesh mesh;
		mesh.CubeInit();

		Geometry::SmartMesh sm;
		int a = sm.CreateAndGo("a");
		sm.CreateCurve([](float lerp) -> DirectX::XMFLOAT3
			{
				return { 2*lerp - 1.0f, -0.5f, 0.0f };
			}
		);
		sm.Step(-1);
		int b = sm.CreateAndGo("b");
		sm.CreateCurve([](float lerp) -> DirectX::XMFLOAT3
			{
				return { 2*lerp - 1.0f, 0.5f, 0.0f };
			}
		);
		Geometry::Fibre fa(sm, a);
		Geometry::Fibre fb(sm, b);
		sm.AddPatch(Geometry::Patch(fa, fb));
		//mesh = sm.GetMesh();
		m_gfx.AddDrawCall(&mesh, "Default", "Default", "Default",
			Topology::TriangleList, "Default", "Expensive");

	}

	void Engine::Run()
	{
		Time::Hourglass frameTime;
		while (ProcessMessages())
		{
			if (m_keyboard.IsKeyDown(VK_ESCAPE)) exit(0);
			frameTime.Start();
						
			HID::Focus->Interact(m_keyboard, m_mouse);
			m_gfx.Update();

			frameTime.Stop();
			Time::DeltaTime = frameTime.GetDelta();
			Time::FPS = frameTime.GetTick();
		}
	}

	void Engine::ShutDown()
	{
		CoUninitialize();
	}

	LRESULT Engine::WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
		{
			//System::Graphics::Resize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

}