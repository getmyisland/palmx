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