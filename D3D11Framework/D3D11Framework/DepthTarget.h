#pragma once

#include <memory>

class Texture;
struct ID3D11DepthStencilView;

class DepthTarget
{
public:
	DepthTarget(std::shared_ptr<Texture> texture);

	void Clear();

	ID3D11DepthStencilView* GetDXHandle();

private:
	ID3D11DepthStencilView* dsv;
	std::shared_ptr<Texture> texture;
};
