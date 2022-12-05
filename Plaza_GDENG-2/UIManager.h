#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "CreditsScreen.h"
#include "StateScreen.h"
#include "AUIScreen.h"
#include <vector>
#include <unordered_map>

class UINames {
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String STATE_SCREEN = "STATE_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";	
};

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* get();
	static void init(HWND hwnd);
	static void destroy();
	void showCreditsMenu();
	void hideCredits();
	void showColorP();
	void hideColor();
	void showEState();
	void hideState();
	void drawUI();
	bool drawCube();
	bool drawPlane();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

	bool cube = false;
	bool plane = false;
private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator = (UIManager const&) {};
	static UIManager* sharedInstance;
	bool showCredits = false;
	bool showColor = false;
	bool showState = false;
	UIList uiList;
	UITable uiTable;

	
};

