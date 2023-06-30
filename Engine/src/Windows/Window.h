#pragma once
#define NOMINMAX
#include <Windows.h>
#include <memory>
#include <string>
#include <HID/Mouse.h>
#include <HID/Keyboard.h>
#include <Utility/ErrorHandling/Result.h>
#include <Utility/ErrorHandling/HResult.h>
#include <Utility/Converter/String.h>
#include <dwmapi.h>


namespace Duat {

	class Window {
	public:
		Window();
		~Window();
		HWND InitWindow(const std::string& title, const std::string& className,
			const LONG& width, const LONG& height, const LONG& x, const LONG& y);
		bool ProcessMessages();
		LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		// WindowProcEx allows to separate custom msg handling code from defaults like keyboard and mouse input
		virtual inline LRESULT WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		std::string GetWindowTitle() const;
		std::string GetWindowClassName() const;
		HWND GetWindowHandle() const;
		HINSTANCE GetWindowInstance() const;
		LONG GetWindowWidth() const;
		LONG GetWindowHeight() const;
		LONG GetWindowPosX() const;
		LONG GetWindowPosY() const;
	protected:
		Utility::HResult m_hresult;

		Keyboard        m_keyboard;
		Mouse           m_mouse;

		std::wstring    m_title;
		std::wstring    m_className;
		HWND            m_hWnd;
		HINSTANCE       m_hInstance;
		LONG            m_width;
		LONG            m_height;
		LONG            m_x;
		LONG            m_y;
	};

}