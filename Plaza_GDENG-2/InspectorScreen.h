#pragma once

#include "AUIScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"
#include "Vector3D.h"

class UIManager;

class InspectorScreen : public AUIScreen
{
private:
	InspectorScreen();
	~InspectorScreen();
	virtual void drawUI() override;
	friend class UIManager;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	char buf[15] = { 0 };
};

