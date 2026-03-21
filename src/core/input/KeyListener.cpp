#include "KeyListener.h"

#if defined(GAS_PLATFORM_GLFW)
#include "../../platform/glfw/input/KeyListenerGLFW.cpp"
#else
#error "No platform defined"
#endif