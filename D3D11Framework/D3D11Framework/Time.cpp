#include "Time.h"

#include "Graphics.h"

float Time::GetDeltaTime()
{
	return Graphics::Singleton().delta_time;
}
