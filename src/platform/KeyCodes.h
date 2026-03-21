#pragma once

#include "KeyList.h"

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