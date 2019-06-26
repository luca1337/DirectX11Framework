#pragma once

#include "Component.h"
#include <memory>
#include <vector>

class Transform;

class Actor : public std::enable_shared_from_this<Actor>
{

protected:

	void InternalAddComponent(std::shared_ptr<Component> Component);

public:
	Actor();

	std::vector<std::shared_ptr<Component>> Components;
	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void FixedTick(float fixed_delta_time);

	template<typename T>
	std::shared_ptr<T> GetComponent() const
	{
		for (int i = 0; i < Components.size(); i++)
		{
			if (T::Type == Components[i]->ComponentType)
			{
				std::shared_ptr<Component> FoundComponent = Components[i];
				return std::dynamic_pointer_cast<T>(FoundComponent);
			}
		}

		return nullptr;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> GetComponents() const
	{
		std::vector<std::shared_ptr<T>> FoundComponents;
		for (int i = 0; i < Components.size(); i++)
		{
			if (T::Type == Components[i]->ComponentType)
			{
				auto FoundComponent = std::dynamic_pointer_cast<T>(Components[i]);
				FoundComponents.push_back(FoundComponent);
			}
		}

		return FoundComponents;
	}

	template<typename T>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> NewComponent = std::make_shared<T>();
		InternalAddComponent(NewComponent);
		NewComponent->ComponentType = T::Type;
		printf("assigned ComponentType to %u\n", NewComponent->ComponentType);
		return NewComponent;
	}

	template<typename T>
	std::shared_ptr<T> AddComponent(std::shared_ptr<T> component)
	{
		InternalAddComponent(component);
		component->ComponentType = T::Type;
		printf("assigned ComponentType to %u\n", component->ComponentType);
		return component;
	}

	std::shared_ptr<Transform> transform;
};