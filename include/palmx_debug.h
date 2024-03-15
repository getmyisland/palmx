/**********************************************************************************************
*
*   palmx - debug functions
*
*	MIT License
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#ifndef PALMX_DEBUG_H
#define PALMX_DEBUG_H

#include <source_location>
#include <sstream>

namespace palmx
{
    //----------------------------------------------------------------------------------
    // Enumerators Definition
    //----------------------------------------------------------------------------------

    enum Severity
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4
    };

    //----------------------------------------------------------------------------------
    // Log Functions
    //----------------------------------------------------------------------------------

    extern void Log(const Severity severity, std::source_location const source, const std::ostringstream& oss);
}

#define PALMX_TRACE(...) { std::ostringstream oss; oss << __VA_ARGS__; ::palmx::Log((::palmx::Severity)0, std::source_location::current(), oss); }
#define PALMX_INFO(...) { std::ostringstream oss; oss << __VA_ARGS__; ::palmx::Log((::palmx::Severity)1, std::source_location::current(), oss); }
#define PALMX_WARN(...) { std::ostringstream oss; oss << __VA_ARGS__; ::palmx::Log((::palmx::Severity)2, std::source_location::current(), oss); }
#define PALMX_ERROR(...) { std::ostringstream oss; oss << __VA_ARGS__; ::palmx::Log((::palmx::Severity)3, std::source_location::current(), oss); }
#define PALMX_CRITICAL(...) { std::ostringstream oss; oss << __VA_ARGS__; ::palmx::Log((::palmx::Severity)4, std::source_location::current(), oss); }

#endif // PALMX_DEBUG_H