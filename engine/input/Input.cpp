#include "Input.h"

namespace PalmEngine
{
	Input::Input() {}
	
	bool Input::GetKeyDown(KeyCode keyCode)
	{
		return _keyCodeToKeyStates.at(keyCode) == KeyState::KEY_DOWN;
	}

	bool Input::GetKey(KeyCode keyCode)
	{
		return _keyCodeToKeyStates.at(keyCode) == KeyState::KEY_PRESS;
	}
		
	bool Input::GetKeyUp(KeyCode keyCode)
	{
		return _keyCodeToKeyStates.at(keyCode) == KeyState::KEY_UP;
	}

	void Input::SetKeyStates(GLFWwindow* window)
	{
		// Set the state for each key
		// A separate implementation of this may be overkill
		// Maybe use glfw system instead
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			_keyCodeToKeyStates[KEY_ARROW_UP] = KEY_PRESS;
		}
		else
		{
			_keyCodeToKeyStates[KEY_ARROW_UP] = KEY_DEFAULT;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			_keyCodeToKeyStates[KEY_ARROW_DOWN] = KEY_PRESS;
		}
		else
		{
			_keyCodeToKeyStates[KEY_ARROW_DOWN] = KEY_DEFAULT;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			_keyCodeToKeyStates[KEY_ARROW_LEFT] = KEY_PRESS;
		}
		else
		{
			_keyCodeToKeyStates[KEY_ARROW_LEFT] = KEY_DEFAULT;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			_keyCodeToKeyStates[KEY_ARROW_RIGHT] = KEY_PRESS;
		}
		else
		{
			_keyCodeToKeyStates[KEY_ARROW_RIGHT] = KEY_DEFAULT;
		}
	}
}