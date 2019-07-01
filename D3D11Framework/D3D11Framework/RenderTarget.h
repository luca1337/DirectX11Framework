#pragma once

#include <memory>

class Texture;
class DepthTarget;
struct D3D11_VIEWPORT;
struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;

class RenderTarget
{
public:
	RenderTarget(std::shared_ptr<Texture> texture);

	void Bind(std::shared_ptr<DepthTarget> depth_target = nullptr);

	void Clear(std::initializer_list<float> color);

	ID3D11RenderTargetView1* GetDXHandle() { return rtv; }

private:
	ID3D11DepthStencilView* depth_view;
	ID3D11RenderTargetView1* rtv;
	std::shared_ptr<Texture> texture;
};
