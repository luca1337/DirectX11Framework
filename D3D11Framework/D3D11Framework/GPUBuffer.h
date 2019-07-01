#pragma once

#include <memory>

class Device;
struct ID3D11Buffer;

class GPUBuffer
{
public:
	GPUBuffer(std::shared_ptr<Device> device, unsigned int size, unsigned int stride, const void* data = nullptr);

	void Bind(unsigned int slot);

	~GPUBuffer();

	ID3D11Buffer* GetDXHandle();

private:
	ID3D11Buffer* buffer;
	std::shared_ptr<Device> device;
	unsigned int stride;
};
