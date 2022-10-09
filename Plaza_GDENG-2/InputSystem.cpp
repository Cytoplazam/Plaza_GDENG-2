#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

float InputSystem::translateXP(float x)
{
	x += 0.01;
	return x;
}

float InputSystem::translateXN(float x)
{
	x -= 0.01;
	return x;
}

float InputSystem::translateYP(float y)
{
	y += 0.01;
	return y;
}

float InputSystem::translateYN(float y)
{
	y -= 0.01;
	return y;
}

float InputSystem::scaleXP(float x)
{
	x += 0.01;
	return x;
}

float InputSystem::scaleXN(float x)
{
	x -= 0.01;
	return x;
}

float InputSystem::scaleYP(float y)
{
	y += 0.01;
	return y;
}

float InputSystem::scaleYN(float y)
{
	y -= 0.01;
	return y;
}
