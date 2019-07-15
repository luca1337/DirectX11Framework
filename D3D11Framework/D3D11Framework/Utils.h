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
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f),
	SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	32.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::red_material = std::make_shared<Material>
(
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(1.0f, 0.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::green_material = std::make_shared<Material>
(
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(0.0f, 1.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::blue_material = std::make_shared<Material>
(
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f),
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	128.0f,
	false,
	false
	);

std::shared_ptr<Material> Utils::yellow_material = std::make_shared<Material>
(
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(0.1f, 0.18f, 0.17f, 1.0f),
	SimpleMath::Vector4(0.39f, 0.74f, 0.69f, 1.0f),
	SimpleMath::Vector4(0.29f, 0.30f, 0.30f, 1.0f),
	12.8f,
	false,
	false
	);

std::shared_ptr<Material> Utils::white_material = std::make_shared<Material>
(
	SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
	SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
	SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	128.0f,
	false,
	false
	);