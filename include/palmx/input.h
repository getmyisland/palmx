#ifndef PALMX_INPUT_H
#define PALMX_INPUT_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <unordered_map>

namespace palmx
{
	enum KeyState
	{
		KEY_DEFAULT,
		KEY_DOWN,
		KEY_PRESS,
		KEY_UP
	};

	struct Key
	{
		KeyState key_state{ KEY_DEFAULT };
		KeyState last_key_state{ KEY_DEFAULT };
	};

	class Input
	{
	public:
		static bool GetKeyDown(int glfw_key_code);
		static bool GetKey(int glfw_key_code);
		static bool GetKeyUp(int glfw_key_code);

		static void SetKeyStates(GLFWwindow* window);

		static void MouseCallback(GLFWwindow* window, double x_pos_in, double y_pos_in);
		static glm::vec2 GetMouseOffset();
		static void ResetMouseOffset();

		static void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
		static glm::vec2 GetMouseWheelOffset();
		static void ResetMouseWheelOffset();

	private:
		Input();

		static void SetKeyState(GLFWwindow* window, int glfw_key_code, Key& key);
		static inline std::unordered_map<int, Key> keys_ = std::unordered_map<int, Key>();

		static inline bool is_first_mouse_input_ = true;
		static inline bool mouse_callback_this_frame_ = false;
		static inline glm::vec2 last_mouse_pos_ = glm::vec2();
		static inline glm::vec2 mouse_offset_ = glm::vec2();

		static inline bool mouse_wheel_callback_this_frame_ = false;
		static inline glm::vec2 mouse_wheel_offset_ = glm::vec2();
	};
}

#endif