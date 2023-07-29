#include "input.h"

namespace palmx
{
	Input::Input() {}

	bool Input::GetKeyDown(int glfw_key_code)
	{
		if (!keys_.contains(glfw_key_code)) 
		{
			keys_.insert(std::pair(glfw_key_code, Key()));
		}

		auto iter = keys_.find(glfw_key_code);
		if (iter != keys_.end())
		{
			const Key& key = iter->second;
			return key.key_state == KeyState::KEY_DOWN;
		}

		return false;
	}

	bool Input::GetKey(int glfw_key_code)
	{
		if (!keys_.contains(glfw_key_code))
		{
			keys_.insert(std::pair(glfw_key_code, Key()));
		}

		auto iter = keys_.find(glfw_key_code);
		if (iter != keys_.end())
		{
			const Key& key = iter->second;
			return key.key_state == KeyState::KEY_PRESS;
		}

		return false;
	}

	bool Input::GetKeyUp(int glfw_key_code)
	{
		if (!keys_.contains(glfw_key_code))
		{
			keys_.insert(std::pair(glfw_key_code, Key()));
		}

		auto iter = keys_.find(glfw_key_code);
		if (iter != keys_.end())
		{
			const Key& key = iter->second;
			return key.key_state == KeyState::KEY_UP;
		}

		return false;
	}

	void Input::SetKeyStates(GLFWwindow* window)
	{
		for (auto& [key, value] : keys_)
		{
			SetKeyState(window, key, value);
		}
	}

	void Input::SetKeyState(GLFWwindow* window, int glfw_key_code, Key& key)
	{
		key.last_key_state = key.key_state;

		if (glfwGetKey(window, glfw_key_code) == GLFW_PRESS)
		{
			if (key.last_key_state == KEY_DEFAULT)
			{
				key.key_state = KEY_DOWN;
			}
			else
			{
				key.key_state = KEY_PRESS;
			}
		}
		else
		{
			if (key.last_key_state == KEY_PRESS)
			{
				key.key_state = KEY_UP;
			}
			else
			{
				key.key_state = KEY_DEFAULT;
			}
		}
	}

	void Input::MouseCallback(GLFWwindow* window, double y_pos_in, double x_pos_in)
	{
		float x_pos = static_cast<float>(-x_pos_in);
		float y_pos = static_cast<float>(-y_pos_in);

		if (is_first_mouse_input_)
		{
			last_mouse_pos_ = glm::vec2(x_pos, y_pos);
			is_first_mouse_input_ = false;
		}

		float x_offset = x_pos - last_mouse_pos_.x;
		float y_offset = last_mouse_pos_.y - y_pos; // Reversed since y-Coordinates go from bottom to top

		last_mouse_pos_ = glm::vec2(x_pos, y_pos);
		mouse_offset_ = glm::vec2(x_offset, y_offset);

		mouse_callback_this_frame_ = true;
	}

	glm::vec2 Input::GetMouseOffset()
	{
		return mouse_offset_;
	}

	void Input::ResetMouseOffset()
	{
		if (mouse_callback_this_frame_)
		{
			mouse_callback_this_frame_ = false;
		}
		else
		{
			mouse_offset_ = glm::vec2();
		}
	}

	void Input::ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
	{
		mouse_wheel_offset_ = glm::vec2(static_cast<float>(x_offset), static_cast<float>(y_offset));

		mouse_wheel_callback_this_frame_ = true;
	}

	glm::vec2 Input::GetMouseWheelOffset()
	{
		return mouse_wheel_offset_;
	}

	void Input::ResetMouseWheelOffset()
	{
		if (mouse_wheel_callback_this_frame_)
		{
			mouse_wheel_callback_this_frame_ = false;
		}
		else
		{
			mouse_wheel_offset_ = glm::vec2();
		}
	}
}