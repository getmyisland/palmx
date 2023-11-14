#include "palmx_core.h"

#include <palmx.h>
#include <palmx_debug.h>

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace palmx
{
    //----------------------------------------------------------------------------------
    // Enumerators Definition
    //----------------------------------------------------------------------------------

    enum KeyState
    {
        KEY_IDLE,
        KEY_DOWN,
        KEY_PRESS,
        KEY_UP
    };

    //----------------------------------------------------------------------------------
    // Structures Definition
    //----------------------------------------------------------------------------------

    struct Key
    {
        KeyState key_state { KEY_IDLE };
        KeyState last_key_state { KEY_IDLE };
    };

    struct Keyboard
    {
        KeyCode exit_key { KeyCode::KEY_ESCAPE };
    };

    struct Mouse
    {
        bool is_first_mouse_input { true };
        bool mouse_callback_this_frame { false };
        glm::vec2 last_mouse_pos;
        glm::vec2 mouse_offset;
        bool mouse_wheel_callback_this_frame { false };
        glm::vec2 mouse_wheel_offset;
    };

    //----------------------------------------------------------------------------------
    // Global Variables Definition
    //----------------------------------------------------------------------------------

    Keyboard keyboard;
    Mouse mouse;

    const std::unordered_map<KeyCode, int> glfw_keys = std::unordered_map<KeyCode, int>() = {
                {KEY_ESCAPE, GLFW_KEY_ESCAPE},
                {KEY_W, GLFW_KEY_W},
                {KEY_A, GLFW_KEY_A},
                {KEY_S, GLFW_KEY_S},
                {KEY_D, GLFW_KEY_D},
    };

    std::unordered_map<KeyCode, Key> keys = std::unordered_map<KeyCode, Key>();

    void SetExitKey(KeyCode key_code)
    {
        keyboard.exit_key = key_code;
    }

    void MouseCallback(GLFWwindow* window, double y_pos_in, double x_pos_in)
    {
        float x_pos = static_cast<float>(-x_pos_in);
        float y_pos = static_cast<float>(-y_pos_in);

        if (mouse.is_first_mouse_input)
        {
            mouse.last_mouse_pos = glm::vec2(x_pos, y_pos);
            mouse.is_first_mouse_input = false;
        }

        float x_offset = x_pos - mouse.last_mouse_pos.x;
        float y_offset = mouse.last_mouse_pos.y - y_pos; // Reversed since y-Coordinates go from bottom to top

        mouse.last_mouse_pos = glm::vec2(x_pos, y_pos);
        mouse.mouse_offset = glm::vec2(x_offset, y_offset);

        mouse.mouse_callback_this_frame = true;
    }

    void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
    {
        mouse.mouse_wheel_offset = glm::vec2(static_cast<float>(x_offset), static_cast<float>(y_offset));

        mouse.mouse_wheel_callback_this_frame = true;
    }

    void SetupInput()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glfwSetCursorPosCallback(px_data.window, MouseCallback);
        glfwSetScrollCallback(px_data.window, ScrollCallback);
    }

    void ResetMouseOffset()
    {
        if (mouse.mouse_callback_this_frame)
        {
            mouse.mouse_callback_this_frame = false;
        }
        else
        {
            mouse.mouse_offset = glm::vec2();
        }
    }

    void ResetMouseWheelOffset()
    {
        if (mouse.mouse_wheel_callback_this_frame)
        {
            mouse.mouse_wheel_callback_this_frame = false;
        }
        else
        {
            mouse.mouse_wheel_offset = glm::vec2();
        }
    }

    void CollectInput()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        for (auto& [key_code, key] : keys)
        {
            if (!glfw_keys.contains(key_code))
            {
                // key code is not registered
                return;
            }

            int glfw_key_code = glfw_keys.at(key_code);

            key.last_key_state = key.key_state;

            if (glfwGetKey(px_data.window, glfw_key_code) == GLFW_PRESS)
            {
                if (key.last_key_state == KEY_IDLE)
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
                    key.key_state = KEY_IDLE;
                }
            }
        }

        ResetMouseOffset();
        ResetMouseWheelOffset();

        if (IsKeyDown(keyboard.exit_key))
        {
            LogInfo("Exit key pressed");
            glfwSetWindowShouldClose(px_data.window, true);
        }
    }

    bool IsKeyDown(KeyCode key_code)
    {
        if (!keys.contains(key_code))
        {
            keys.insert(std::pair(key_code, Key()));
        }

        auto iter = keys.find(key_code);
        if (iter != keys.end())
        {
            const Key& key = iter->second;
            return key.key_state == KeyState::KEY_DOWN;
        }

        return false;
    }

    bool IsKeyPressed(KeyCode key_code)
    {
        if (!keys.contains(key_code))
        {
            keys.insert(std::pair(key_code, Key()));
        }

        auto iter = keys.find(key_code);
        if (iter != keys.end())
        {
            const Key& key = iter->second;
            return key.key_state == KeyState::KEY_PRESS;
        }

        return false;
    }

    bool IsKeyUp(KeyCode key_code)
    {
        if (!keys.contains(key_code))
        {
            keys.insert(std::pair(key_code, Key()));
        }

        auto iter = keys.find(key_code);
        if (iter != keys.end())
        {
            const Key& key = iter->second;
            return key.key_state == KeyState::KEY_UP;
        }

        return false;
    }

    glm::vec2 GetMouseOffset()
    {
        return mouse.mouse_offset;
    }

    glm::vec2 GetMouseWheelOffset()
    {
        return mouse.mouse_wheel_offset;
    }

    void ShowCursor()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void HideCursor()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void UnlockCursor()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void LockCursor()
    {
        if (!px_data.init)
        {
            LogError("palmx not initialized");
            return;
        }

        glfwSetInputMode(px_data.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}