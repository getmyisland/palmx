#ifndef _PE_RESOURCE_MANAGER_H__
#define _PE_RESOURCE_MANAGER_H__

#include <string>

namespace PalmEngine
{
	class ResourceManager {
	private:
		ResourceManager() {};
		~ResourceManager() {};

	public:
		static std::string GetProjectRootDirectory();
		static std::string GetFileContentAsString(std::string& filePath);
	};
}

#endif