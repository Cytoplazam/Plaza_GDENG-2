#pragma once

#include "AUIScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "UIManager.h"

class UIManager;

class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen();
	~CreditsScreen();
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	virtual void drawUI() override;
	friend class UIManager;
	ID3D11ShaderResourceView* my_texture;
};

