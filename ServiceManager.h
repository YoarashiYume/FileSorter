#pragma once
#include <string>
#include <Windows.h>
namespace ServiceLib::ServiceManagement
{
	/**
	\brief Service Manager for service management
	*/
	class ServiceManager
	{
	public:
		/**
		\brief Service Manager for service management
		\param serviceName service name
		\param servicePath path to service
		*/
		ServiceManager( const std::u16string& serviceName, const std::u16string& servicePath)
			: m_serviceName(serviceName)
			, m_servicePath(servicePath)
		{ }
		/**
		\brief service install method
		\return 0 if everything is correct, otherwise error code
		*/
		int InstallService();
		/**
		\brief service uninstall method
		\return 0 if everything is correct, otherwise error code
		*/
		int UninstallService();
		/**
		\brief service run method
		\return 0 if everything is correct, otherwise error code
		*/
		int RunService();

	private:
		std::u16string m_serviceName;///< service name
		std::u16string m_servicePath;///< path to service
	};
}
