#include "Window.h"

#if defined(GAS_PLATFORM_GLFW)
#include "../platform/glfw/WindowGLFW.cpp"
#else
#error "No platform defined"
#endif