#pragma once

#include <PxPhysicsAPI.h>

class DX11FWDispatcher : public physx::PxCpuDispatcher
{
public:
	DX11FWDispatcher()
	{
		// spawn the thread
	}

	virtual void submitTask(physx::PxBaseTask& task) override
	{
		task.run();
		task.release();
	}

	virtual uint32_t getWorkerCount() const override
	{
		return 0;
	}
};