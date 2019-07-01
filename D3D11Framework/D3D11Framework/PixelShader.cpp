#include "PixelShader.h"
#include "Device.h"

#include "Core.h"

PixelShader::PixelShader(std::shared_ptr<Device> device, const void * byte_code, size_t byte_code_size) : device(device)
{
	if (device->GetDXHandle()->CreatePixelShader(byte_code, byte_code_size, nullptr, &pixel_shader) != S_OK)
	{
		throw std::exception("unable to create pixel shader");
	}
}

void PixelShader::Bind()
{
	device->GetDXContext()->PSSetShader(pixel_shader, nullptr, 0);
}
