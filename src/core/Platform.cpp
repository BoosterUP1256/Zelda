#include "Platform.h"

#if defined(GAS_PLATFORM_GLFW)
#include "../platform/glfw/PlatformGLFW.cpp"
#else
#error "No platform defined"
#endif