#pragma once

#include "Core.h"
#include <SimpleMath.h>

struct Mvp
{
	DirectX::SimpleMath::Matrix model;
	DirectX::SimpleMath::Matrix view;
	DirectX::SimpleMath::Matrix projection;
};