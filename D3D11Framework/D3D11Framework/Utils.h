#pragma once

#include <memory>

struct Material;

struct Utils
{
	// -- BASE COLOR MATERIALS --
	static std::shared_ptr<Material> default_material;
	static std::shared_ptr<Material> red_material;
	static std::shared_ptr<Material> green_material;
	static std::shared_ptr<Material> blue_material;
	static std::shared_ptr<Material> yellow_material;
	static std::shared_ptr<Material> white_material;

	// -- SPECIAL MATERIALS --
};

std::shared_ptr<Material> Utils::default_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	32.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::red_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::green_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::blue_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::yellow_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(0.1, 0.18725, 0.1745, 1.0),
	DirectX::XMFLOAT4(0.396, 0.74151, 0.69102, 1.0),
	DirectX::XMFLOAT4(0.297254, 0.30829, 0.306678, 1.0),
	12.8f,
	false,
	false
	);

std::shared_ptr<Material> Utils::white_material = std::make_shared<Material>
(
	DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
	DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);