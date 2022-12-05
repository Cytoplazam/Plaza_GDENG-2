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
				//SceneWriter::get()->WriteToFile();
			}
			if (ImGui::MenuItem("Color Picker"))
			{
				UIManager::get()->showColorP();
			}
			if (ImGui::MenuItem("Engine States"))
			{
				UIManager::get()->showEState();
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
		if (ImGui::BeginMenu("Primitives"))
		{
			if (ImGui::MenuItem("Physics Cube"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PCUBE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			if (ImGui::MenuItem("Physics Plane"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PPLANE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	//ImGui::End();
}
