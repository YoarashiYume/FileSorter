#include "Watcher.h"

std::string Watcher::getFolder(const std::string& extent) const
{
	if (extent.size() > sizeof(uint64_t))
	{
		auto res = unstandartSetting.find(extent);
		if (res == unstandartSetting.end())
			return {};
		return res->second;
	}
	uint64_t tempW =0 ;
	std::memcpy(&tempW, extent.data(), extent.size());
	auto res = setting.find(tempW);
	if (res == setting.end())
		return{};
	return res->second;
}

void Watcher::Copy(const std::string& folder, const std::filesystem::path& path, const std::filesystem::path& filePath)
{
	//bulid new path
	std::filesystem::path newPath = path.string() + "\\" + folder + "\\" + filePath.filename().string();
	if (std::filesystem::exists(newPath))
	{
		//if a similar file exists, then add the current date
		newPath = path.string() + "\\" + folder + "\\" + filePath.stem().string();
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		newPath += " " + std::to_string(now->tm_mday) + "." + std::to_string(now->tm_mon+1) + "." + std::to_string(now->tm_year%100) +
			" " + std::to_string(now->tm_hour) + "_" + std::to_string(now->tm_min) + "_" + std::to_string(now->tm_sec)+filePath.extension().string();
	}
	if (!std::filesystem::exists(path.string() + "\\" + folder))
		std::filesystem::create_directory(path.string() + "\\" + folder); //create a directory if it doesn't exist
	if (std::filesystem::copy_file(filePath, newPath)) //trying to copy a file
	{
		std::error_code ec;
		std::filesystem::remove(filePath,ec);//	trying to remove a file
		if (ec.value())
		{
			//if it fails, then delete the copied file
			std::filesystem::remove(newPath);
			log->out("Error with \"" + filePath.string() + "\" with remove");
		}
		else
			log->out(filePath, newPath);
	}
	else
		log->out("Error with \"" + filePath.string() + "\" with copy");
}

Watcher::Watcher(const std::map<std::string, std::string>& _map, const std::vector<std::string>& _wPath,
	const std::filesystem::path& _setPath, std::shared_ptr<Logger> log)
{
	this->log = log;
	uint64_t tempW;
	setPath = _setPath;
	for (auto& el : _wPath)
		wPath.emplace_back(el);
	log->out("update Path, count =" + std::to_string(wPath.size()));
	for (auto& el : _map)
	{
		if (el.first.size() > sizeof(tempW))
			unstandartSetting[el.first] = el.second;
		else
		{
			std::memcpy(&tempW, el.first.data(), el.first.size());
			setting[tempW] = el.second;
			tempW = 0;
		}
	}
	log->out("update FolderInfo, count =" + std::to_string(unstandartSetting.size()+ setting.size()));
}

void Watcher::start()
{
	std::string folder;
	for (auto & pathEl : wPath)
		for (auto& file : std::filesystem::directory_iterator(pathEl))
		{
			if (file.is_block_file())
				continue;
			if (file.is_directory())
				continue;
			if (file.path() == setPath)//configuration file is not copied
				continue;
			folder = getFolder(file.path().extension().string());
			if (folder.empty())
				continue;
			Copy(folder, pathEl, file.path());
		}
}
