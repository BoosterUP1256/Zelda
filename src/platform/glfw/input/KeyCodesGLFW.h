#pragma once

#define GAS_KEY_LIST \
    X(A, GLFW_KEY_A) \
    X(D, GLFW_KEY_D) \
    X(W, GLFW_KEY_W) \
    X(S, GLFW_KEY_S) \
    X(Space, GLFW_KEY_SPACE)

namespace Gas {

    enum class Key
    {
        
#define X(name, glfw) name,
        GAS_KEY_LIST
#undef X

        Count,
        Unknown = -1
    };

}