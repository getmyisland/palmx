/**********************************************************************************************
*
*   palmx - interaction with local filesystem
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

#include <palmx.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <direct.h>
#define GET_CURRENT_DIR _getcwd
#elif __linux__
#include <unistd.h>
#define GET_CURRENT_DIR getcwd
#endif

namespace palmx
{
    std::string GetRootDirectory()
    {
        char buff[FILENAME_MAX]; // Create string buffer to hold path
        char* content = GET_CURRENT_DIR(buff, FILENAME_MAX);
        if (content != NULL)
        {
            return content;
        }
        else
        {
            return "";
        }
    }

    std::string GetAbsolutePath(const std::string relative_path)
    {
        std::string root_dir = GetRootDirectory();
        if (root_dir == "")
        {
            return "";
        }

        return root_dir + relative_path;
    }
}