#pragma once

#include <PxPhysicsAPI.h>
#include <iostream>

class DX11FWAllocator : public physx::PxAllocatorCallback
{
	void* allocate(size_t size, const char* typeName, const char* filename, int line) override
	{
		return std::malloc(size);
	}

	void deallocate(void* ptr) override
	{
		std::free(ptr);
	}
};
