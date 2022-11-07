#pragma once
#include "InputListener.h"
#include <map>
#include "Point.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPos(const Point& pos);
	void showCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

public:
	static InputSystem* get();
private:
	std::map<InputListener*, InputListener*> m_map_listener;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point oldMousePos;
	bool firstTime = true;
};


