#include "MenuScreen.h"

MenuScreen::MenuScreen():AUIScreen("Menu")
{
	//ImGui::FileBrowser saveFileDialog;

	saveFileDialog = ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);

	saveFileDialog.SetTitle("Save File");
	saveFileDialog.SetTypeFilters({ ".iet" });

	//ImGui::FileBrowser loadFileDialog;

	loadFileDialog = ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);

	loadFileDialog.SetTitle("Open File");
	loadFileDialog.SetTypeFilters({ ".iet" });
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
				GameObjectManager::get()->createObject(GameObjectManager::CUBE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			if (ImGui::MenuItem("Physics Cube"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PCUBE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			if (ImGui::MenuItem("Plane"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PLANE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			if (ImGui::MenuItem("Physics Plane"))
			{
				GameObjectManager::get()->createObject(GameObjectManager::PPLANE, nullptr, 0);//, Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	saveFileDialog.Display();

	if (saveFileDialog.HasSelected())
	{
		//std::cout << "Selected filename: " << saveFileDialog.GetSelected().string() << std::endl;
		//saveFileDialog.ClearSelected();
		SceneWriter writer = SceneWriter(this->saveFileDialog.GetSelected().string());
		writer.WriteToFile();
		this->saveFileDialog.ClearSelected();
		this->saveFileDialog.Close();
	}

	loadFileDialog.Display();

	if (loadFileDialog.HasSelected())
	{
	}
	//ImGui::End();
}
