#include "HeirarchyScreen.h"

HeirarchyScreen::HeirarchyScreen() :AUIScreen("hierarchy")
{
}

HeirarchyScreen::~HeirarchyScreen()
{
}

void HeirarchyScreen::drawUI()
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (ImGui::Begin("Hierarchy Window"))
	{
		for (int i = 0; i < GameObjectManager::get()->getAllObjects().size(); i++)
		{
			if (ImGui::Button(GameObjectManager::get()->getAllObjects()[i]->getName().c_str(), ImVec2(120, 0)))
			{
				GameObjectManager::get()->setSelectedObject(GameObjectManager::get()->getAllObjects()[i]);
			}
				
		}
	}

	ImGui::End();
}
