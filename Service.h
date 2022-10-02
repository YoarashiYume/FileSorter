#pragma once
#include <memory>
#include <string>
#include <Windows.h>

namespace ServiceLib::ServiceManagement
{
	/**
	\brief Class to start and stop windows service
	*/
	class Service
	{
	public:
		/**
		\brief Constructor
		\param serviceName service name
		*/
		Service(const std::u16string& serviceName);
		/**
		\brief Method returning service name
		\param Service::m_serviceName
		*/
		const std::u16string& GetName() const;
		/**
		\brief Service start method
		\return 0 if everything is correct, otherwise error code
		*/
		int Start();
		/**
		\brief Service stop method
		*/
		void Stop();
		/**
		\brief Service shutdown method
		*/
		void Shutdown();
		/**
		\brief Method that changes the state of a service
		*/
		void NotifyState();
		virtual ~Service() = default;

	protected:
		/**
		\method that executes once after the service is started
		\return 0 if everything is correct, otherwise error code
		*/
		virtual int Init() = 0;
		/**
		\brief Method that executes while the service is running
		*/
		virtual void DoWork() = 0;
		/**
		\method that executes once after the service is stoped
		\return 0 if everything is correct, otherwise error code
		*/
		virtual int DoStop() = 0;

	private:
		std::u16string m_serviceName;///< service name

		SERVICE_STATUS m_serviceStatus;///< current service status
		SERVICE_STATUS_HANDLE m_serviceStatusHandle;///< Handle with status information for the current service
	};

	/**
	\brief Factory to create the service
	*/
	struct IServiceFactory
	{
		/**
		\service creation method
		\return an instance of the Service class
		*/		
		virtual std::unique_ptr<Service> Create() = 0;
	};
}
