#pragma once

#include "Core.h"
#include <SimpleMath.h>

struct ShadowMapMvp
{
	DirectX::SimpleMath::Matrix view;
	DirectX::SimpleMath::Matrix projection;
};