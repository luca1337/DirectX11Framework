#include "ShaderObject.h"

ShaderObject::ShaderObject(Texture texture) : texture(texture)
{
	if (Engine::Singleton().GetDxDevice()->GetDXHandle()->CreateShaderResourceView1(texture.GetDXHandle(), nullptr, &srv) != S_OK)
	{
		throw std::exception("unable to create shader resource view");
	}
}

void ShaderObject::Bind(UINT gpu_register)
{
	Engine::Singleton().GetDxDevice()->GetDXContext()->PSSetShaderResources(gpu_register, 1, (ID3D11ShaderResourceView**)&srv);
}

void ShaderObject::Unbind(UINT gpu_register)
{
	ID3D11ShaderResourceView* nullsrv[1] = { nullptr };
	Engine::Singleton().GetDxDevice()->GetDXContext()->PSSetShaderResources(gpu_register, 1, nullsrv);
}
