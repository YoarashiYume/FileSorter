#pragma once
#include "Service.h"
#include <stdexcept>
namespace ServiceLib::ServiceManagement
{
	/**
	\brief function to initialize the service
	\param serviceFactory service creation factory
	*/
	//function to initialize the service
	void InitService( IServiceFactory& serviceFactory);
}