#ifndef _PE_INPUT_H__
#define _PE_INPUT_H__

#include <vector>
#include <map>

#include <GLFW/glfw3.h>

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

	class Input
	{
	public:
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKey(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static void SetKeyStates(GLFWwindow* window);

	private:
		Input();

		static inline std::map<KeyCode, KeyState> _keyCodeToKeyStates = std::map<KeyCode, KeyState>(
			{
				{	KEY_ARROW_UP, KEY_DEFAULT
				},
			});
	};
}

#endif