#pragma once

#include "InputSystem.h"
#include <queue>

class Keyboard
{
public:
	Keyboard();
	bool KeyIsPressed(const unsigned char keycode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	InputSystem ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];
	std::queue<InputSystem> keyBuffer;
	std::queue<unsigned char> charBuffer;
};

