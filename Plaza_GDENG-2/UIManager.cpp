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
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
