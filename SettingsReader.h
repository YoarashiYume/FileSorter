#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
/**
\brief class that reads the configuration file
*/
class SettingsReader final
{
private:
	std::vector<std::string> wPath; ///< directories to be monitored
	std::map<std::string, std::string> sortSet;///< sort settings - {extension - directories}
public:
	/**
	\brief Constructor
	\param path path to configuration file
	*/
	SettingsReader(const std::string& path);
	/**
	\brief returns a list of directories to monitor
	\param SettingsReader::wPath
	*/
	std::vector<std::string> getPath() const; 
	/**
	\brief returns sort settings
	\param SettingsReader::sortSet
	*/
	std::map<std::string, std::string> getSetting() const;
};

