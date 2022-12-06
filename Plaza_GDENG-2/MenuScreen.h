#pragma once

#include "AUIScreen.h"
#include "imgui.h"
#include "imfilebrowser.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"

class UIManager;

class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();
	virtual void drawUI() override;
	friend class UIManager;
	bool my_tool_active = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui::FileBrowser saveFileDialog;
	ImGui::FileBrowser loadFileDialog;
};

