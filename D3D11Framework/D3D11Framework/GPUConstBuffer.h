#pragma once

#include <memory>

class Device;
struct ID3D11Buffer;

class GPUConstBuffer
{
public:
	GPUConstBuffer(std::shared_ptr<Device> device, unsigned int size, const void* data = nullptr);

	void BindInVertex(unsigned int gpu_register, void* data);

	void BindInPixel(unsigned int gpu_register, void* data, unsigned int num_buffers);

	ID3D11Buffer* GetDXHandle();

private:
	ID3D11Buffer* buffer;
	std::shared_ptr<Device> device;
};
