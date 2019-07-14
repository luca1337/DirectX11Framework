#pragma once

#include <memory>
#include <CommonStates.h>

class Adapter;
struct ID3D11BlendState;
struct ID3D11Device5;
struct ID3D11DeviceContext4;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct ID3D11SamplerState;
struct D3D11_RASTERIZER_DESC;

class Device
{
public:
	Device(std::shared_ptr<Adapter> adapter);

	void Draw(unsigned int vertices_num);

	void TurnOffCulling();

	void TurnOnBackCulling();

	void TurnOnWireframeRendering();

	void TurnOffWireframeRendering();

	void TurnOffZBuffer();

	void TurnOnZBuffer();

	ID3D11Device5* GetDXHandle();

	ID3D11DeviceContext4* GetDXContext();

	std::unique_ptr<DirectX::CommonStates> states; // RAII
private:

	
	void CreateRasterizerState(D3D11_RASTERIZER_DESC rs_desc);

	void BindRasterizerState();

	ID3D11BlendState* Transparency;
	ID3D11Device5* device;
	ID3D11DeviceContext4* context;
	ID3D11RasterizerState* rs;
	ID3D11DepthStencilState* dss;
	ID3D11SamplerState* ss;
};