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
		int num = GameObjectManager::get()->getAllObjects().size();
		ImGui::Text("Number of Objects: %i", num);
		for (int i = 0; i < GameObjectManager::get()->getAllObjects().size(); i++)
		{
			if (ImGui::Button(GameObjectManager::get()->getAllObjects()[i]->getName().c_str(), ImVec2(150, 0)))
			{
				GameObjectManager::get()->setSelectedObject(GameObjectManager::get()->getAllObjects()[i]);
			}
				
		}
	}

	ImGui::End();
}
