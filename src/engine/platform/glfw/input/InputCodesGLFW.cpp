#include "InputCodesGLFW.h"
#include <GLFW/glfw3.h>
#include <array>

namespace Gas {

    constexpr std::array<Key, GLFW_KEY_LAST + 1> createKeyMap()
    {
        std::array<Key, GLFW_KEY_LAST + 1> map{};

        for (int i = 0; i <= GLFW_KEY_LAST; i++)
            map[i] = Key::Unknown;

#define X(name, glfw) map[glfw] = Key::name;
        GAS_GLFW_KEY_MAP
#undef X

        return map;
    }

    constexpr std::array<MouseButton, GLFW_MOUSE_BUTTON_LAST + 1> createMouseButtonMap()
    {
        std::array<MouseButton, GLFW_MOUSE_BUTTON_LAST + 1> map{};
        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
            map[i] = MouseButton::Unknown;

#define X(name, glfw) map[glfw] = MouseButton::name;
        GAS_GLFW_MOUSE_BUTTON_MAP
#undef X

        return map;
    }

    static constexpr auto s_glfwKeyMap         = createKeyMap();
    static constexpr auto s_glfwMouseButtonMap = createMouseButtonMap();

    Key GLFW::toKey(int glfwKey)
    {
        if (glfwKey < 0 || glfwKey > GLFW_KEY_LAST)
            return Key::Unknown;

        return s_glfwKeyMap[glfwKey];
    }

    MouseButton GLFW::toMouseButton(int glfwMouseButton)
    {
        if (glfwMouseButton < 0 || glfwMouseButton > GLFW_MOUSE_BUTTON_LAST)
            return MouseButton::Unknown;
        
        return s_glfwMouseButtonMap[glfwMouseButton];
    }

    Action GLFW::toAction(int glfwAction)
    {
        switch (glfwAction)
        {
            case GLFW_PRESS:   return Action::Press;   
            case GLFW_RELEASE: return Action::Release; 
            case GLFW_REPEAT:  return Action::Repeat;  
            default:           return Action::Unknown;
        }
    }

}