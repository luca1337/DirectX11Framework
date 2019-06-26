#pragma once

#include "Device.h"
#include <Keyboard.h>

#include "DxMenu.h"

class Window
{
public:
	Window(std::shared_ptr<Device> device, UINT width, UINT height, std::string title);

	void Present()
	{

		// bit blit the back buffer to the front buffer, waiting for vsync
		swap_chain->Present(1, 0);
	}

	ID3D11Texture2D* GetDXTexture()
	{
		ID3D11Texture2D* swap_chain_texture = nullptr;
		if (swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&swap_chain_texture) != S_OK)
		{
			throw std::exception("unable to get the swap chain texture");
		}
		return swap_chain_texture;
	}

	std::shared_ptr<Device> GetDevice()
	{
		return device;
	}

private:
	std::string window_class_name;
	HINSTANCE win32_instance;
	std::shared_ptr<Device> device;
	IDXGISwapChain1* swap_chain;
	HWND window;
	UINT width;
	UINT height;
};