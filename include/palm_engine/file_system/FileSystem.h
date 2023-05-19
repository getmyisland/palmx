#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>

class FileSystem {
private:
	FileSystem() {};

public:
	static std::string GetProjectRootDirectory();
	static std::string GetFileContent(std::string filePath);
};

#endif