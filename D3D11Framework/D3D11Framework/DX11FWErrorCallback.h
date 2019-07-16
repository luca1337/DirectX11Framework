#pragma once

#include <PxPhysicsAPI.h>
#include <iostream>

class DX11FWErrorCallback : public physx::PxErrorCallback
{
	void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
	{
		std::cerr << message << std::endl;
	}
};