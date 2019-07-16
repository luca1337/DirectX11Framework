#include "Utils.h"
#include "Material.h"
#include "PhysicsMaterial.h"

// -- MESH MATERIALS -- //
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