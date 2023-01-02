#ifndef MODULES_H
#define MODULES_H
#ifdef _WIN32
#pragma once
#endif

#include "input/InputModule.h"
#include "graphics/GraphicModule.h"

namespace Module
{
	// All modules listed here
	extern InputModule g_InputSystem;
	extern GraphicModule g_GraphicSystem;
}

#endif // MODULES_H