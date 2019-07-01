#include "DepthTarget.h"

#include "Engine.h"
#include "Device.h"
#include "Texture.h"

DepthTarget::DepthTarget(std::shared_ptr<Texture> texture) : texture(texture), dsv(nullptr)
{
	// a render target view is an object able to receive rasterization
		// output (like an opengl framebuffer)
	if (Engine::Singleton().GetDxDevice()->GetDXHandle()->CreateDepthStencilView(texture->GetDXHandle(), nullptr, &dsv) != S_OK)
	{
		throw std::exception("unable to create depth stencil view");
	}
}

void DepthTarget::Clear()
{
	Engine::Singleton().GetDxDevice()->GetDXContext()->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

ID3D11DepthStencilView * DepthTarget::GetDXHandle()
{
	return dsv;;
}
