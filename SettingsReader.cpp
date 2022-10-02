#include "SettingsReader.h"

SettingsReader::SettingsReader(const std::string& path)
{
	std::ifstream reader(path);
	if (!reader.is_open())
		return;
	std::string readLine,iFolder;
	bool isOpen = false;
	while (std::getline(reader, readLine))
	{
		//try to find folder path
		if (readLine.find("= {") == std::string::npos && !isOpen)
			wPath.emplace_back(readLine);
		//try to find sort struct "FOLDER = {extension}"
		else if (readLine.find("= {") != std::string::npos)
		{
			iFolder = readLine.substr(0, readLine.find("= {"));
			isOpen = true;
		}
		else if (readLine.find("}") != std::string::npos)
			isOpen = false;
		else
			sortSet[readLine] = iFolder;
	}
}

std::vector<std::string> SettingsReader::getPath() const
{
	return wPath;
}

std::map<std::string, std::string> SettingsReader::getSetting() const
{
	return sortSet;
}
