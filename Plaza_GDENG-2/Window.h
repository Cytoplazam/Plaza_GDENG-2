#pragma once
#include <Windows.h>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"
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
	virtual void onFocus();
	virtual void onKillFocus();


	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

