#pragma once

//#include <pvd/PxPvd.h>
#include <PxPhysicsAPI.h>
#include <string>
#include <iostream>

namespace d3d_engine
{
	static physx::PxFilterFlags FooShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
	{
		// let object fall trough
		if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		// default for collisions
		pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}

	class CustomSimulationEvent : public physx::PxSimulationEventCallback
	{

		void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override
		{
			std::cout << "callback event !!!" << std::endl;
		}

		// Inherited via PxSimulationEventCallback
		void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override
		{
		}

		void onWake(physx::PxActor** actors, physx::PxU32 count) override
		{
		}

		void onSleep(physx::PxActor** actors, physx::PxU32 count) override
		{
		}

		void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override
		{
			std::cout << "triggered!!!!!!!!!!!!!!!!!!!" << std::endl;
		}

		void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override
		{
		}
	};

	class CustomAllocator : public physx::PxAllocatorCallback
	{
		// Inherited via PxAllocatorCallback
		void* allocate(size_t size, const char* typeName, const char* filename, int line) override
		{
			//std::cout << "typeName: " << typeName << " filename: " << filename << " line: " << line << std::endl;
			return std::malloc(size);
		}

		void deallocate(void* ptr) override
		{
			std::free(ptr);
		}
	};

	class CustomErrorCallback : public physx::PxErrorCallback
	{
		// Inherited via PxErrorCallback
		void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
		{
			std::cerr << message << std::endl;
		}
	};

	class CustomDispatcher : public physx::PxCpuDispatcher
	{
	public:
		CustomDispatcher()
		{
			// spawn the thread
		}
		// Inherited via PxCpuDispatcher
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

	class Physix
	{
	public:

		// Singleton
		static Physix& Get();

		physx::PxScene* GetPxScene();
		physx::PxPhysics* GetPxPhysics();
		physx::PxMaterial* GetPxMaterial();
		std::shared_ptr<physx::PxSceneDesc> GetPxSceneDesc();
		
		void InitPhysix();

		// this must be done in a separate thread!!
		void UpdatePhysx(float delta_time);

		~Physix();

	private:
		physx::PxScene* scene;
		physx::PxPhysics* physics;
		physx::PxMaterial* material;
		std::shared_ptr<physx::PxSceneDesc> scene_desc;
	};
}