#include "UIManager.h"
#include <iostream>

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getD3Ddevice(), GraphicsEngine::get()->getContext());

	UINames uiNames;

	MenuScreen* menuScreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	StateScreen* stateScreen = new StateScreen();
	this->uiTable[uiNames.STATE_SCREEN] = stateScreen;
	this->uiList.push_back(stateScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	HeirarchyScreen* hierarchyScreen = new HeirarchyScreen();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);
}

UIManager::~UIManager()
{
}

UIManager* UIManager::get()
{
	return sharedInstance;
}

void UIManager::init(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::showCreditsMenu()
{
	showCredits = true;
}

void UIManager::hideCredits()
{
	showCredits = false;
}

void UIManager::showColorP()
{
	showColor = true;
}

void UIManager::hideColor()
{
	showColor = false;
}

void UIManager::showEState()
{
	showState = true;
}

void UIManager::hideState()
{
	showState = false;
}

void UIManager::drawUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//std::cout << this->uiList.size();
	for (int i = 0; i < this->uiList.size(); i++)
	{
		if (this->uiList[i]->getName() == "Credits" && !showCredits)
		{
			continue;
		}
		if (this->uiList[i]->getName() == "profiler" && !showColor)
		{
			continue;
		}
		if (this->uiList[i]->getName() == "State" && !showState)
		{
			continue;
		}
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool UIManager::drawCube()
{
	return cube;
}

bool UIManager::drawPlane()
{
	return plane;
}
