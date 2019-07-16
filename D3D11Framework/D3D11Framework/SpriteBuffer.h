#pragma once

#include "Core.h"
#include <SimpleMath.h>

struct SpriteBuffer
{
	DirectX::SimpleMath::Vector3 color;
	float _pad0;
	BOOL use_texture;
	float _pad1[3];
};