#include "MenuScreen.h"

MenuScreen::MenuScreen():AUIScreen("Menu")
{
	//ImGui::FileBrowser saveFileDialog;

	saveFileDialog = ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);

	saveFileDialog.SetTitle("Save File");
	saveFileDialog.SetTypeFilters({ ".xml" });

	//ImGui::FileBrowser loadFileDialog;

	loadFileDialog = ImGui::FileBrowser();

	loadFileDialog.SetTitle("Open File");
	loadFileDialog.SetTypeFilters({ ".xml" });
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{
	//ImGui::ShowDemoWindow();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				this->saveFileDialog.Open();
			}
			if (ImGui::MenuItem("Open"))
			{
				this->loadFileDialog.Open();
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
			if (ImGui::MenuItem("Cube"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::CUBE, nullptr, 0);
			}
			if (ImGui::MenuItem("Physics Cube"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PCUBE, nullptr, 0);
			}
			if (ImGui::MenuItem("Plane"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PLANE, nullptr, 0);
			}
			if (ImGui::MenuItem("Physics Plane"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PPLANE, nullptr, 0);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	this->saveFileDialog.Display();
	this->loadFileDialog.Display();

	if (this->saveFileDialog.HasSelected())
	{
		SceneWriter writer = SceneWriter(this->saveFileDialog.GetSelected().string());
		writer.WriteToFile();
		this->saveFileDialog.ClearSelected();
		this->saveFileDialog.Close();
	}
	else if (this->loadFileDialog.HasSelected())
	{
		SceneReader reader = SceneReader(this->loadFileDialog.GetSelected().string());
		reader.readFromFile();
		this->loadFileDialog.ClearSelected();
		this->loadFileDialog.Close();
	}
	//ImGui::End();
}
