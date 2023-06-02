#ifndef _PE_INPUT_H__
#define _PE_INPUT_H__

#include <vector>
#include <map>

#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

namespace PalmEngine
{
	enum KeyState
	{
		KEY_DEFAULT,
		KEY_DOWN,
		KEY_PRESS,
		KEY_UP
	};

	enum KeyCode
	{
		KEY_ARROW_UP,
		KEY_ARROW_DOWN,
		KEY_ARROW_LEFT,
		KEY_ARROW_RIGHT
	};

	enum AxisCode
	{
		AXIS_MOUSE,
		AXIS_MOUSE_WHEEL
	};

	class Input
	{
	public:
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKey(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static void SetKeyStates(GLFWwindow* window);
		static void ResetAxisOffset();

		static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static glm::vec2 GetAxis(AxisCode axisCode);

	private:
		Input();

		static inline std::map<KeyCode, KeyState> _keyCodeToKeyStates = std::map<KeyCode, KeyState>(
			{
				{KEY_ARROW_UP, KEY_DEFAULT},
				{KEY_ARROW_DOWN, KEY_DEFAULT},
				{KEY_ARROW_LEFT, KEY_DEFAULT},
				{KEY_ARROW_RIGHT, KEY_DEFAULT},
			}
		);

		static inline float _lastMousePosX = 0;
		static inline float _lastMousePosY = 0;
		static inline bool _firstMouseInput = true;
		static inline bool _mouseCallbackThisFrame = false;
		static inline bool _mouseCallbackLastFrame = false;
		static inline std::map<AxisCode, glm::vec2> _axisCodeToOffset = std::map<AxisCode, glm::vec2>(
			{
				{AXIS_MOUSE, glm::vec2()},
				{AXIS_MOUSE_WHEEL, glm::vec2()}
			}
		);
	};
}

#endif