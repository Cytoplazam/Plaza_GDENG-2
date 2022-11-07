#include "MenuScreen.h"

MenuScreen::MenuScreen():AUIScreen("Menu")
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Color Picker"))
			{
				UIManager::get()->showColorP();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Credits"))
			{
				UIManager::get()->showCreditsMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	//ImGui::End();
}
