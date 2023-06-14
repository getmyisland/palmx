#include "Input.h"

#include <debug/LogManager.h>

namespace palmx
{
	Input::Input() {}

	bool Input::GetKeyDown(KeyCode keyCode)
	{
		auto iter = _keys.find(keyCode);
		if (iter != _keys.end())
		{
			const Key& key = iter->second;
			return key.mKeyState == KeyState::KeyDown;
		}

		return false;
	}

	bool Input::GetKey(KeyCode keyCode)
	{
		auto iter = _keys.find(keyCode);
		if (iter != _keys.end())
		{
			const Key& key = iter->second;
			return key.mKeyState == KeyState::KeyPress;
		}

		return false;
	}

	bool Input::GetKeyUp(KeyCode keyCode)
	{
		auto iter = _keys.find(keyCode);
		if (iter != _keys.end())
		{
			const Key& key = iter->second;
			return key.mKeyState == KeyState::KeyUp;
		}

		return false;
	}

	void Input::SetKeyStates(GLFWwindow* window)
	{
		for (auto& [key, value] : _keys)
		{
			SetKeyState(window, key, value);
		}
	}

	void Input::SetKeyState(GLFWwindow* window, KeyCode keyCode, Key& key)
	{
		key.mLastKeyState = key.mKeyState;

		if (glfwGetKey(window, key.mGlfwKeyCode) == GLFW_PRESS)
		{
			if (key.mLastKeyState == KeyDefault)
			{
				key.mKeyState = KeyDown;
			}
			else
			{
				key.mKeyState = KeyPress;
			}
		}
		else
		{
			if (key.mLastKeyState == KeyPress)
			{
				key.mKeyState = KeyUp;
			}
			else
			{
				key.mKeyState = KeyDefault;
			}
		}
	}

	void Input::MouseCallback(GLFWwindow* window, double yPosIn, double xPosIn)
	{
		float xPos = static_cast<float>(-xPosIn);
		float yPos = static_cast<float>(-yPosIn);

		if (_firstMouseInput)
		{
			_lastMousePos = glm::vec2(xPos, yPos);
			_firstMouseInput = false;
		}

		float xOffset = xPos - _lastMousePos.x;
		float yOffset = _lastMousePos.y - yPos; // Reversed since y-Coordinates go from bottom to top

		_lastMousePos = glm::vec2(xPos, yPos);
		_mouseOffset = glm::vec2(xOffset, yOffset);

		_mouseCallbackThisFrame = true;
	}

	glm::vec2 Input::GetMouseOffset()
	{
		return _mouseOffset;
	}

	void Input::ResetMouseOffset()
	{
		if (_mouseCallbackThisFrame)
		{
			_mouseCallbackThisFrame = false;
			return;
		}

		_mouseOffset = glm::vec2();
	}

	void Input::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		_mouseWheelOffset = glm::vec2(static_cast<float>(xOffset), static_cast<float>(yOffset));
	}
}