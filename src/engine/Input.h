#ifndef _PE_INPUT_H__
#define _PE_INPUT_H__

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

	enum KeyCode
	{
		KeyW,
		KeyS,
		KeyA,
		KeyD
	};

	struct Key
	{
		Key(const unsigned int glfwKeyCode) : mGlfwKeyCode(glfwKeyCode) {}

		const unsigned int mGlfwKeyCode;
		KeyState mKeyState{ KeyDefault };
		KeyState mLastKeyState{ KeyDefault };
	};

	class Input
	{
	public:
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKey(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static void SetKeyStates(GLFWwindow* window);
		
		static void MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
		static glm::vec2 GetMouseOffset();
		static void ResetMouseOffset();

		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static glm::vec2 GetMouseWheelOffset();
		static void ResetMouseWheelOffset();

	private:
		Input();

		static void SetKeyState(GLFWwindow* window, Key& key);
		static inline std::unordered_map<KeyCode, Key> _keys = std::unordered_map<KeyCode, Key>(
			{
				{KeyW, Key(GLFW_KEY_W)},
				{KeyS, Key(GLFW_KEY_S)},
				{KeyA, Key(GLFW_KEY_A)},
				{KeyD, Key(GLFW_KEY_D)}
			}
		);

		static inline bool _firstMouseInput = true;
		static inline bool _mouseCallbackThisFrame = false;
		static inline glm::vec2 _lastMousePos = glm::vec2();
		static inline glm::vec2 _mouseOffset = glm::vec2();

		static inline bool _mouseWheelCallbackThisFrame = false;
		static inline glm::vec2 _mouseWheelOffset = glm::vec2();
	};
}

#endif