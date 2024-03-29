#include "Window.h"

#include <Keyboard.h>
#include "Core.h"
#include "DX.h"
#include "Engine.h"
#include "Device.h"


extern LRESULT WINAPI ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::Window(unsigned int width, unsigned int height, std::string title) : width(width), height(height), swap_chain(nullptr)
{
	window_class_name = title + "_class";
	win32_instance = GetModuleHandle(nullptr);
	// create a win32 window class (required for creating windows)
	WNDCLASS wclass = {};
	wclass.lpszClassName = window_class_name.c_str();
	wclass.hInstance = win32_instance;
	wclass.lpfnWndProc = WndProc;

	RegisterClass(&wclass);

	// the window size is cutted by the border/caption size, so
	// we need to compute the right window size for having
	// a drawable area of 1024x1024

	DWORD style = WS_CAPTION;
	RECT rect = { 0, 0, (LONG)width, (LONG)height };

	// this will compute the right dimension
	AdjustWindowRect(&rect, style, false);

	window = CreateWindow(window_class_name.c_str(), title.c_str(),
		style, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, win32_instance, nullptr);

	if (!window)
	{
		throw std::exception("unable to create window");
	}

	DXGI_SWAP_CHAIN_DESC1 sc_desc = {};
	sc_desc.BufferCount = 1;
	sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sc_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // or DXGI_FORMAT_R16G16B16A16_FLOAT
	sc_desc.SampleDesc.Count = 4;
	sc_desc.SampleDesc.Quality = 0;
	sc_desc.Width = width;
	sc_desc.Height = height;
	sc_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (DX::GetFactory()->CreateSwapChainForHwnd(
		Engine::Singleton().GetDxDevice()->GetDXHandle(),
		window,
		&sc_desc,
		nullptr,
		nullptr,
		&swap_chain) != S_OK)
	{
		throw std::exception("unable to create the swap chain");
	}

	// make the window visible (win32)
	ShowWindow(window, SW_SHOW);

}

void Window::Present()
{
	// bit blit the back buffer to the front buffer, waiting for vsync
	swap_chain->Present(1, 0);
}

ID3D11Texture2D * Window::GetDXTexture()
{
	ID3D11Texture2D* swap_chain_texture = nullptr;
	if (swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&swap_chain_texture) != S_OK)
	{
		throw std::exception("unable to get the swap chain texture");
	}
	return swap_chain_texture;
}