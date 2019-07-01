#include "GPUConstBuffer.h"
#include "Device.h"

#include "Core.h"

GPUConstBuffer::GPUConstBuffer(std::shared_ptr<Device> device, unsigned int size, const void * data) : device(device), buffer(nullptr)
{
	D3D11_BUFFER_DESC buf_desc = {};
	buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buf_desc.ByteWidth = size;
	buf_desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA* buf_data_ptr = nullptr;

	if (data)
	{
		// like textures, but without pitching
		D3D11_SUBRESOURCE_DATA buf_data = {};
		buf_data.pSysMem = data;
		buf_data_ptr = &buf_data;
	}

	if (device->GetDXHandle()->CreateBuffer(&buf_desc, buf_data_ptr, &buffer) != S_OK)
	{
		throw std::exception("unable to create constant buffer");
	}
}

void GPUConstBuffer::BindInVertex(unsigned int gpu_register, void * data)
{
	device->GetDXContext()->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	device->GetDXContext()->VSSetConstantBuffers(gpu_register, 1, &buffer);
}

void GPUConstBuffer::BindInPixel(unsigned int gpu_register, void * data, unsigned int num_buffers)
{
	device->GetDXContext()->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
	device->GetDXContext()->PSSetConstantBuffers(gpu_register, num_buffers, &buffer);
}

ID3D11Buffer* GPUConstBuffer::GetDXHandle()
{
	return buffer;
}
