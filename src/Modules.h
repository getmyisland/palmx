#ifndef MODULES_H
#define MODULES_H
#ifdef _WIN32
#pragma once
#endif

#include "input/InputModule.h"
#include "graphics/GraphicModule.h"

namespace Modules
{
	// All modules listed here
	extern InputModule g_InputModule;
	extern GraphicModule g_GraphicModule;
}

#endif // MODULES_H