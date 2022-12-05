#include "StateScreen.h"

StateScreen::StateScreen() :AUIScreen("State")
{
}

StateScreen::~StateScreen()
{
}

void StateScreen::drawUI()
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (ImGui::Begin("Engine State Menu"))
	{
		if (!paused)
			state = "Pause";
		else
			state = "Play";

		if (ImGui::Button(state.c_str()))
		{
			if (!paused)
				paused = true;
			else
				paused = false;
		}
		
		ImGui::SameLine();
		if (ImGui::Button("Undo"))
		{

		}
		ImGui::SameLine();
		if (ImGui::Button("Redo"))
		{

		}

		if (ImGui::Button("Close"))
		{
			UIManager::get()->hideState();
		}
	}

	ImGui::End();
}
