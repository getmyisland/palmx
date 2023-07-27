#ifndef PALMX_INPUT_H
#define PALMX_INPUT_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <unordered_map>

namespace palmx
{
	enum KeyState
	{
		KeyDefault,
		KeyDown,
		KeyPress,
		KeyUp
	};

	struct Key
	{
		KeyState mKeyState{ KeyDefault };
		KeyState mLastKeyState{ KeyDefault };
	};

	class Input
	{
	public:
		static bool GetKeyDown(int glfwKeyCode);
		static bool GetKey(int glfwKeyCode);
		static bool GetKeyUp(int glfwKeyCode);

		static void SetKeyStates(GLFWwindow* window);
		
		static void MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
		static glm::vec2 GetMouseOffset();
		static void ResetMouseOffset();

		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static glm::vec2 GetMouseWheelOffset();
		static void ResetMouseWheelOffset();

	private:
		Input();

		static void SetKeyState(GLFWwindow* window, int glfwKeyCode, Key& key);
		static inline std::unordered_map<int, Key> _keys = std::unordered_map<int, Key>();

		static inline bool _firstMouseInput = true;
		static inline bool _mouseCallbackThisFrame = false;
		static inline glm::vec2 _lastMousePos = glm::vec2();
		static inline glm::vec2 _mouseOffset = glm::vec2();

		static inline bool _mouseWheelCallbackThisFrame = false;
		static inline glm::vec2 _mouseWheelOffset = glm::vec2();
	};
}

#endif