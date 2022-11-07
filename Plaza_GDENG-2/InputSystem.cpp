#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT mousePos = {};
	::GetCursorPos(&mousePos);

	if (firstTime)
	{
		oldMousePos = Point(mousePos.x, mousePos.y);
		firstTime = false;
	}

	if (mousePos.x != oldMousePos.x || mousePos.y != oldMousePos.y)
	{
		std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

		while (it != m_map_listener.end())
		{
			it->second->onMouseMove(Point(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y));
			it++;
		}
	}

	oldMousePos = Point(mousePos.x, mousePos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keys_state[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

				while (it != m_map_listener.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onLMD(Point(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y));
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onRMD(Point(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y));
						}
					}
					else
						it->second->onKeyDown(i);

					it++;
				}
			}
			else
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

					while (it != m_map_listener.end())
					{
						if (i == VK_LBUTTON)
							it->second->onLMU(Point(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y));
						else if (i == VK_RBUTTON)
							it->second->onRMU(Point(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y));
						else
							it->second->onKeyUp(i);

						it++;
					}
				}
			}
		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_map_listener.insert(std::make_pair<InputListener*, InputListener*>
		(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));

}

void InputSystem::removeListener(InputListener* listener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_listener.find(listener);

	if (it != m_map_listener.end())
	{
		m_map_listener.erase(it);
	}
}

void InputSystem::setCursorPos(const Point& pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keys_state[i] & 0x80 && i == key)
			return true;
		if (i == key)
			return false;
	}
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if (!(m_keys_state[i] & 0x80) && i == key)
			return true;
		else if (i == key)
			return false;
	}
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}


