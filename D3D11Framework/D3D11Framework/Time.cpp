#include "Time.h"

#include "GraphicsSystem.h"

float Time::GetDeltaTime()
{
	return GraphicSystem::Get().delta_time;
}
