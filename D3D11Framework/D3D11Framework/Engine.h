#pragma once

#include <memory>

class Adapter;
class Device;

class Engine final
{
public:
	static Engine& Singleton();

	std::shared_ptr<Adapter> GetDxAdapter() const;
	std::shared_ptr<Device> GetDxDevice() const;

	template<typename T>
	void RegisterComponent()
	{
		T::Type = ++component_counter;
		printf("assigned %u to the new type\n", T::Type);
	}

private:
	Engine();

	unsigned int component_counter;

	std::shared_ptr<Adapter> adapter;
	std::shared_ptr<Device> device;
};