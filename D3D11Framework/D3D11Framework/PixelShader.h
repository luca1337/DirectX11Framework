#pragma once

#include <memory>

class Device;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

class PixelShader
{
public:
	PixelShader(std::shared_ptr<Device> device, const void* byte_code, size_t byte_code_size);

	void Bind();

private:
	std::shared_ptr<Device> device;
	ID3D11PixelShader* pixel_shader;
	ID3D11InputLayout* input_layout;
};
