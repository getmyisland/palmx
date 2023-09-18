#ifndef PALMX_INPUT_H
#define PALMX_INPUT_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <unordered_map>

namespace palmx
{
	enum KeyCode
	{
		KEY_W,
		KEY_A,
		KEY_S,
		KEY_D
	};

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
		static bool GetKeyDown(KeyCode key_code);
		static bool GetKey(KeyCode key_code);
		static bool GetKeyUp(KeyCode key_code);

		static void SetKeyStates(GLFWwindow* window);

		static void MouseCallback(GLFWwindow* window, double x_pos_in, double y_pos_in);
		static glm::vec2 GetMouseOffset();
		static void ResetMouseOffset();

		static void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
		static glm::vec2 GetMouseWheelOffset();
		static void ResetMouseWheelOffset();

	private:
		Input();

		static void SetKeyState(GLFWwindow* window, KeyCode key_code, Key& key);
		static inline std::unordered_map<KeyCode, Key> keys_ = std::unordered_map<KeyCode, Key>();

		static inline std::unordered_map<KeyCode, int> glfw_keys_ = std::unordered_map<KeyCode, int>() = {
			{KEY_W, GLFW_KEY_W},
			{KEY_A, GLFW_KEY_A},
			{KEY_S, GLFW_KEY_S},
			{KEY_D, GLFW_KEY_D},
		};

		static inline bool is_first_mouse_input_ = true;
		static inline bool mouse_callback_this_frame_ = false;
		static inline glm::vec2 last_mouse_pos_ = glm::vec2();
		static inline glm::vec2 mouse_offset_ = glm::vec2();

		static inline bool mouse_wheel_callback_this_frame_ = false;
		static inline glm::vec2 mouse_wheel_offset_ = glm::vec2();
	};
}

#endif