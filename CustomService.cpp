#include "CustomService.h"
#include <thread>
#include <fstream>

namespace Custom::ServiceApp
{
	int CustomService::Init()
	{
		//parameter initialization
		settingsPath = std::filesystem::current_path().string() + "\\CopyWorkersettings.txt";
		p_log.reset(new Logger(std::filesystem::current_path().string() + "\\CopyWorkerLog.txt"));
		p_log->out("Start");
		//reading a configuration file
		SettingsReader setReader(settingsPath.string());
		p_watcher.reset(new Watcher(setReader.getSetting(), setReader.getPath(), settingsPath,p_log));
		lastSettingTime = std::filesystem::last_write_time(settingsPath);
		return 0;
	}

	void CustomService::DoWork()
	{
		std::this_thread::sleep_for(std::chrono::seconds(60));//directory check every minute
		p_watcher->start();
		//	checking settings change
		if (lastSettingTime != std::filesystem::last_write_time(settingsPath))
		{
			lastSettingTime = std::filesystem::last_write_time(settingsPath);
			SettingsReader setReader(settingsPath.string());
			p_watcher.reset(new Watcher(setReader.getSetting(), setReader.getPath(), settingsPath,p_log));
		}
	}

	int CustomService::DoStop()
	{
		p_log->out("Shutdown\n");
		return 0;
	}


	std::unique_ptr<ServiceLib::ServiceManagement::Service> CustomServiceFactory::Create()
	{
		return std::make_unique<CustomService>();
	}
}