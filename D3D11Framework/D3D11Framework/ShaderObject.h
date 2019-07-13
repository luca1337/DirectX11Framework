#pragma once

#include "Texture.h"
#include "Engine.h"
#include "Device.h"

class ShaderObject
{
public:
	ShaderObject(Texture texture);

	void Bind(UINT gpu_register);

	void Unbind(UINT gpu_register);

private:
	ID3D11ShaderResourceView1* srv;
	Texture texture;
};
