#pragma once

#include <memory>

#include "Core.h"
#include <SimpleMath.h>

struct Material;

using namespace DirectX;

struct Utils
{
	// -- BASE COLOR MATERIALS --
	static std::shared_ptr<Material> default_material;
	static std::shared_ptr<Material> red_material;
	static std::shared_ptr<Material> green_material;
	static std::shared_ptr<Material> blue_material;
	static std::shared_ptr<Material> white_material;

	// 2D materials
	static std::shared_ptr<Material> default_sprite_material;
};