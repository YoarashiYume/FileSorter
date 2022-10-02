#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <map>
#include <chrono>
/**
\brief Class that checks for changes to a file in a directory
*/
class Watcher final
{
private:
	std::unordered_map<uint64_t, std::string> setting;///< sort settings - {extension - directories} if extension < sizeof(uint64_t)
	std::unordered_map<std::string, std::string> unstandartSetting;///< sort settings - {extension - directories}
	std::shared_ptr<Logger> log;///< logger	
	std::vector<std::filesystem::path> wPath; ///< directories to be monitored
	std::filesystem::path setPath;///< path to configuration file (to avoid deletion)
	/**
	\brief method tries to find the folder for the given extension
	\param extent file extension
	\return folder
	*/
	std::string getFolder(const std::string& extent) const;
	/**
	\brief method transfer file
	\param folder name of the sort folder for the file
	\param path current file folder
	\param path path to the file in the current folder
	*/
	void Copy(const std::string& folder,const std::filesystem::path& path, const std::filesystem::path& filePath);
public:
	/**
	\brief Constructor
	\param _map sort settings
	\param _wPath directories to be monitored
	\param _setPath path to configuration file
	\param log logger
	*/
	Watcher(const std::map<std::string, std::string>& _map,const std::vector<std::string>& _wPath,
		const std::filesystem::path& _setPath, std::shared_ptr<Logger> log);
	/**
	\brief method starts checking directories
	*/
	void start();
};

