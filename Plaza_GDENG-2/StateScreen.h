#pragma once

#include "AUIScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"

class UIManager;

class StateScreen: public AUIScreen
{
	StateScreen();
	~StateScreen();
	virtual void drawUI() override;
	friend class UIManager;
	bool paused = false;
	String state = "Play";
	bool my_tool_active = true;
};

