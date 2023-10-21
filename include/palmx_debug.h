/**********************************************************************************************
*
*   palmx - Debug functions to help with resolving bugs.
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Licensed under the MIT License. See LICENSE.md for full details.
*
**********************************************************************************************/

#ifndef PALMX_DEBUG_H
#define PALMX_DEBUG_H

#include <source_location>
#include <string>

namespace palmx
{
    //----------------------------------------------------------------------------------
    // Log Functions
    //----------------------------------------------------------------------------------
    extern void LogInfo(std::string const message, std::source_location const source = std::source_location::current());
    extern void LogWarning(std::string const message, std::source_location const source = std::source_location::current());
    extern void LogError(std::string const message, std::source_location const source = std::source_location::current());
}

#endif // PALMX_DEBUG_H