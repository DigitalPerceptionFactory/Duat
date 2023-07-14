#pragma once
#include <tuple>
#include <random>
#include <future>
#include "Window.h"
#include <Graphics/System.h>


namespace Duat
{

	class Engine : public Window
	{
	public:
		Engine(std::string title, size_t width = 0, size_t height = 0);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;

		void StartUp();
		void Run();
		void ShutDown();
		float r_sin(float x) { return x; };
	private:
		LRESULT     WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		HINSTANCE   m_hInstance;
		Utility::Result  m_result;
		Utility::HResult m_hresult;
		Graphics::System m_gfx;
	};

}