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
		m_gfx.Init(m_hWnd, 8, 1);

		Graphics::Object3D skybox(m_gfx);
		skybox.SetMesh(Geometry::Cube());
		skybox.Set(Graphics::Preset::Skybox);
		skybox.SetTexture("skybox");
		skybox.DrawCallEnabled(1);

		static Graphics::PointLight light(m_gfx);
		//light.SetPosition(-3, 1, 2);
		light.SetPosition(0, 0, -5);
		light.SetScale(0.25, 0.25, 0.25);
		light.SetIntensity(0.5);
		m_gfx.AddLight("Sun", &light);
				
		static Geometry::Mesh mesh;
		mesh.TestInit();
		
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
		/*m_gfx.AddDrawCall(&mesh, "Default", "Default", "Default",
			Topology::TriangleList, "Default", "Expensive");*/

		Geometry::Dodecahedron dod;
		dod.SetVertexColor(0, 0, 0.3);
		Geometry::Icosahedron ico;
		ico.SetVertexColor(0, 0, 0.1, 0.3);

		Geometry::Mesh finalMesh;
		finalMesh.AppendMesh(dod);
		//finalMesh.AppendMesh(ico);
				
		static Geometry::Grid g(&m_gfx, 10,10);
		//g.ps = "Texture";
		g.SetRS_MultisampleEnabled(1);
		//g.DrawCallEnabled(true);

		static Graphics::Object3D model(m_gfx, finalMesh, Graphics::GraphicsObject());
		model.SetRS_CullMode(Cull::None);
		model.DrawCallEnabled(true);
		//model.DrawCallEnabled(false);
		
		static Graphics::Object3D rightPlane(m_gfx, Geometry::Quad(), Graphics::GraphicsObject());
		rightPlane.SetVertexColor(0, 0.3, 0);
		rightPlane.DrawCallEnabled(1);
		rightPlane.Scale(10, 5, 1);
		rightPlane.Translate(5, 0, 0);
		rightPlane.Rotate(0, 90, 0);
		static Graphics::Object3D backPlane(m_gfx, Geometry::Quad(), Graphics::GraphicsObject());
		backPlane.SetVertexColor(0, 0.3, 0);
		backPlane.DrawCallEnabled(1);
		backPlane.Scale(10, 5, 1);
		backPlane.Translate(0, 0, 5);
		static Graphics::Object3D botPlane(m_gfx, Geometry::Quad(), Graphics::GraphicsObject());
		botPlane.SetVertexColor(0, 0.3, 0);
		botPlane.DrawCallEnabled(1);
		botPlane.Scale(10, 10, 1);
		botPlane.Translate(0, -2.5, 0);
		botPlane.Rotate(90, 0, 0);

		light.GizmoEnabled(1);
				
		Geometry::Mesh splineMesh;
		Geometry::Spline spline;
		spline.Append(Geometry::Bezier_Cubic(
			{ -3, 0, 0 }, { -3, 3, 0 }, { 3, 3, 0 }, { 3, 0, 0 }
		));
		spline.Append(Geometry::Bezier_Cubic(
			{ 3, 0, 0 }, { 3, 5, 0 }, { 6, 5, 0 }, { 6, 0, 0 }
		));
		auto splinePoints = spline.Get(100, 0, 1);
		std::vector<Geometry::Vertex> vertices;
		for (int i = 0; i < splinePoints.size(); ++i)
		{
			Geometry::Vertex vtx;
			vtx.position = splinePoints[i];
			vtx.color = { 1,1,1,1 };
			vertices.push_back(vtx);
		}
		splineMesh.SetVertices(vertices);
		splineMesh.GeneratePointListIndices();
		//m_gfx.AddDrawCall(&splineMesh, "Default", "Default", "Default",
		//	Topology::PointList, "Default", "Expensive");
	}

	void Engine::Run()
	{
		Time::Hourglass frameTime;
		while (ProcessMessages())
		{
			if (m_keyboard.IsKeyDown(VK_ESCAPE)) exit(0);

			frameTime.Start();
			
			//if (m_keyboard.IsKeyDown(VK_RETURN)) m_Forex.Close("Capybara");

			if (m_keyboard.IsKeyDown(VK_F1)) HID::Selection = m_gfx.GetCamera("Default");
			if (m_keyboard.IsKeyDown(VK_F2)) HID::Selection = m_gfx.GetLight("Sun");
			
			HID::Selection->Interact(m_keyboard, m_mouse);
			m_gfx.Update();

			frameTime.Stop();
			Time::DeltaTime = frameTime.GetDelta();
			Time::FPS = frameTime.GetTick();
		}
	}

	void Engine::ShutDown()
	{
		//m_Forex.Exit();
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