#pragma once

#include <string>
#include <memory>

class Device;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11VertexShader;
struct ID3D11InputLayout;

class VertexShader
{
public:
	VertexShader(std::shared_ptr<Device> device, const void* byte_code, size_t byte_code_size, D3D11_INPUT_ELEMENT_DESC* layout, unsigned int layout_size);

	void Bind();

private:
	std::shared_ptr<Device> device;
	ID3D11VertexShader* vertex_shader;
	ID3D11InputLayout* input_layout;
};
