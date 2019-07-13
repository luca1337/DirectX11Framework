#include "VertexShader.h"

#include "Device.h"
#include "Core.h"

VertexShader::VertexShader(std::shared_ptr<Device> device, const void * byte_code, size_t byte_code_size, D3D11_INPUT_ELEMENT_DESC * layout, unsigned int layout_size) : device(device)
{
	if (device->GetDXHandle()->CreateVertexShader(byte_code, byte_code_size, nullptr, &vertex_shader) != S_OK)
	{
		throw std::exception("unable to create vertex shader");
	}

	// not the input layout is validated with the shader bytecode/opcodes
	if (device->GetDXHandle()->CreateInputLayout(layout, layout_size, byte_code, byte_code_size, &input_layout) != S_OK)
	{
		throw std::exception("unable to create input layout");
	}
}

void VertexShader::Bind()
{
	device->GetDXContext()->IASetInputLayout(input_layout);
	device->GetDXContext()->VSSetShader(vertex_shader, nullptr, 0);
}
