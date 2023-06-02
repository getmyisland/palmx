#include "Input.h"

#include <logging/LogManager.h>

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

	void Input::ResetAxisOffset()
	{
		// Dirty trick to check if the mouse offset should be resetted
		// TODO Do this for Mouse Wheel
		if (_mouseCallbackThisFrame)
		{
			_mouseCallbackLastFrame = true;
			_mouseCallbackThisFrame = false;
		}

		if (_mouseCallbackLastFrame)
		{
			_mouseCallbackLastFrame = false;
			return;
		}

		for (auto& [key, value] : _axisCodeToOffset)
		{
			value = glm::vec2();
		}
	}

	void Input::MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn)
	{
		float xPos = static_cast<float>(xPosIn);
		float yPos = static_cast<float>(yPosIn);

		if (_firstMouseInput)
		{
			_lastMousePosX = xPos;
			_lastMousePosY = yPos;
			_firstMouseInput = false;
		}

		float xOffset = xPos - _lastMousePosX;
		float yOffset = _lastMousePosY - yPos; // Reversed since y-Coordinates go from bottom to top

		_lastMousePosX = xPos;
		_lastMousePosY = yPos;

		_axisCodeToOffset.at(AXIS_MOUSE) = glm::vec2(xOffset, yOffset);

		_mouseCallbackThisFrame = true;
	}

	void Input::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		_axisCodeToOffset.at(AXIS_MOUSE_WHEEL) = glm::vec2(static_cast<float>(xOffset), static_cast<float>(yOffset));
	}

	glm::vec2 Input::GetAxis(AxisCode axisCode)
	{
		return _axisCodeToOffset.at(axisCode);
	}
}