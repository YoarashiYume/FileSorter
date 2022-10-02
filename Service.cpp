#include "Service.h"
namespace ServiceLib::ServiceManagement
{
	void WINAPI ControlHandler(DWORD request);

	Service::Service(const std::u16string& serviceName)
		:  m_serviceName{ serviceName }
		, m_serviceStatus{ 0 }
		, m_serviceStatusHandle{ 0 }
	{
		m_serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		m_serviceStatus.dwCurrentState = SERVICE_START_PENDING;
		m_serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	}

	const std::u16string& Service::GetName() const
	{
		return m_serviceName;
	}

	int Service::Start()
	{
		m_serviceStatus.dwCurrentState = SERVICE_START_PENDING;
		//Try to register service
		m_serviceStatusHandle = RegisterServiceCtrlHandlerW(reinterpret_cast<LPCWSTR>(m_serviceName.c_str()), (LPHANDLER_FUNCTION)ControlHandler);
		if (m_serviceStatusHandle == (SERVICE_STATUS_HANDLE)0)
			return -1;

		int error = Init();//do Init function
		if (error) 
		{
			m_serviceStatus.dwCurrentState = SERVICE_STOPPED;
			m_serviceStatus.dwWin32ExitCode = error;
			NotifyState();
			return error;
		}
		//notify the system to start the service
		m_serviceStatus.dwCurrentState = SERVICE_RUNNING;
		NotifyState();

		while (m_serviceStatus.dwCurrentState == SERVICE_RUNNING)
			DoWork();//execute service method

		return 0;
	}

	void Service::Stop()
	{
		m_serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;

		NotifyState();
		if (DoStop() == 0)
		{
			m_serviceStatus.dwWin32ExitCode = 0;
			m_serviceStatus.dwCurrentState = SERVICE_STOPPED;
			NotifyState();
		}
	}

	void Service::Shutdown()
	{
		if (DoStop() == 0)
		{
			m_serviceStatus.dwWin32ExitCode = 0;
			m_serviceStatus.dwCurrentState = SERVICE_STOPPED;
			NotifyState();
		}
	}

	void Service::NotifyState()
	{
		SetServiceStatus(m_serviceStatusHandle, &m_serviceStatus);
	}
}

