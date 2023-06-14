#include "ResourceManager.h"

#include <debug/LogManager.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <direct.h>
#define GET_CURRENT_DIR _getcwd

namespace palmx
{
	ResourceManager::ResourceManager() {}
	ResourceManager::~ResourceManager() {}

	template<> ResourceManager* Singleton<ResourceManager>::msSingleton = 0;
	ResourceManager* ResourceManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	ResourceManager& ResourceManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void ResourceManager::StartUp()
	{
		DEBUG_LOG_INFO("Resource Manager initialized");
	}

	void ResourceManager::ShutDown()
	{

	}

	std::string ResourceManager::GetProjectRootDirectory()
	{
		char buff[FILENAME_MAX]; // Create string buffer to hold path
		char* content = GET_CURRENT_DIR(buff, FILENAME_MAX);
		if (content != NULL)
		{
			return std::string(content);
		}
		else
		{
			DEBUG_LOG_WARNING("Could not get project root directory");
			return std::string("");
		}
	}

	std::string ResourceManager::GetFileContentAsString(std::string& filePath)
	{
		std::ifstream file;

		// Ensure ifstream objects can throw exceptions
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// Open files
			file.open(filePath);
			std::stringstream fileStream;
			// Read file's buffer contents into streams
			fileStream << file.rdbuf();
			// Close file handlers
			file.close();
			// Convert stream into string
			return fileStream.str();
		}
		catch (std::ifstream::failure e)
		{
			DEBUG_LOG_ERROR("FILE_NOT_SUCCESFULLY_READ::PATH::" + filePath);
			return std::string("");
		}
	}
}