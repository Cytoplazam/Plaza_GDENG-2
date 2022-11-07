#include "ProfilerScreen.h"

ProfilerScreen::ProfilerScreen():AUIScreen("profiler")
{
}

ProfilerScreen::~ProfilerScreen()
{
}

void ProfilerScreen::drawUI()
{
	ImGuiStyle& style = ImGui::GetStyle();
	
	if (ImGui::Begin("Color Picker"))
	{
		ImGui::ColorPicker3("color", (float*)&clear_color);
		if (ImGui::Button("Close", ImVec2(70.0f, 0.0f)))
		{
			UIManager::get()->hideColor();
		}
	}
	
	ImGui::End();
}
