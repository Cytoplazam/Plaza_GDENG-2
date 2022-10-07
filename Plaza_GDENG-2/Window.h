#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	//initialize window
	bool init();
	bool broadcast();
	//release window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

