#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{

	}
	~InputListener()
	{

	}

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	virtual void onMouseMove(const Point& mousePos) = 0;

	virtual void onLMD(const Point& mousePos) = 0;
	virtual void onLMU(const Point& mousePos) = 0;

	virtual void onRMD(const Point& mousePos) = 0;
	virtual void onRMU(const Point& mousePos) = 0;
};
