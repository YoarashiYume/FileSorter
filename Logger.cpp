#include "Logger.h"

Logger::~Logger()
{
	stream.close();
}

void Logger::out(const std::filesystem::path& from, const  std::filesystem::path& to)
{
	this->out("Copy \"" + from.string() + "\" to \"" + to.string() + "\"");
}

void Logger::out(const std::string& info)
{
	t = std::time(0);
	now = std::localtime(&t);
	//getting the current time
	std::string data{ std::to_string(now->tm_mday) + "." + std::to_string(now->tm_mon+1) + "." + std::to_string(now->tm_year % 100) +" "+
		std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec) };
	stream.open(logPath, std::ios::app);
	stream << "["+ data +"] " + info +"\n";
	stream.close();
}
