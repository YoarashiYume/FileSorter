#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <filesystem>
#include <chrono>
/**
\brief class for writing the results of the service
*/
class Logger final
{
private:
	std::ofstream stream;///< output stream
	std::time_t t;///<structures for getting the current time
	std::tm* now;///<structures for getting the current time
	std::filesystem::path logPath;///< path to log file
public:
	/**
	\brief Constructor
	\param _logPath path to log file
	*/
	Logger(const std::filesystem::path& _logPath) :
		logPath(_logPath) 
	{
		stream.open(logPath, std::ios::app);
		this->out("Start log");
		stream.close();
	};
	~Logger();
	/**
	\brief method displaying information about the transfer of the file to the log
	\param from original path to the file
	\param to path to the file after copying
	*/
	void out(const std::filesystem::path& from,const  std::filesystem::path& to);
	/**
	\brief method of displaying information in the log
	\param info original path to the file information
	*/
	void out(const std::string &info);
};

