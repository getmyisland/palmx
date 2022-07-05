#ifndef SYSTEM_GLOBALS_H
#define SYSTEM_GLOBALS_H
#ifdef _WIN32
#pragma once
#endif

#include "input/InputSystem.h"
#include "graphics/GraphicSystem.h"

namespace System {
	extern InputSystem g_InputSystem;
	extern GraphicSystem g_GraphicSystem;
}

#endif // SYSTEM_GLOBALS_H