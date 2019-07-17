#pragma once

#include <Windows.h>
#include <memory>
#include <string>

class Device;
struct ID3D11Texture2D;
struct IDXGISwapChain1;

class Window
{
public:
	Window(unsigned int width, unsigned int height, std::string title);

	void Present();

	ID3D11Texture2D* GetDXTexture();

private:
	std::string window_class_name;
	HINSTANCE win32_instance;
	IDXGISwapChain1* swap_chain;
	HWND window;
	unsigned int width;
	unsigned int height;
};