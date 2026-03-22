#include "KeyCodesGLFW.h"
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

    static constexpr auto s_glfwKeyMap = createKeyMap();

    Key GLFW::glfwToKey(int glfwKey)
    {
        if (glfwKey < 0 || glfwKey > GLFW_KEY_LAST)
            return Key::Unknown;

        return s_glfwKeyMap[glfwKey];
    }

}