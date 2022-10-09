#pragma once
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	float translateXP(float x);
	float translateXN(float x);
	float translateYP(float y);
	float translateYN(float y);
	float scaleXP(float x);
	float scaleXN(float x);
	float scaleYP(float y);
	float scaleYN(float y);
};


