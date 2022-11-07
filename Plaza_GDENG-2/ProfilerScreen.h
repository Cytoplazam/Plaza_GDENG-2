#pragma once

#include "AUIScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"

class UIManager;

class ProfilerScreen: public AUIScreen
{
private:
	ProfilerScreen();
	~ProfilerScreen();
	virtual void drawUI() override;
	friend class UIManager;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

