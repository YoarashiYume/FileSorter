#pragma once
#include "Service.h"
#include "Watcher.h"
#include "SettingsReader.h"
#include "Logger.h"
#include <memory>
namespace Custom::ServiceApp
{
    /**
    \brief Class to start and stop custom service
    */
    class CustomService final: public ServiceLib::ServiceManagement::Service
    {
    public:
        /**
        \brief Deafult constructor
        */
        CustomService()
            : ServiceLib::ServiceManagement::Service(u"CopyWorker")
        { }

    protected:
        /**
        \method that executes once after the service is started
		\return 0 if everything is correct, otherwise error code
        Method reads the current service settings
        */
        virtual int Init() override;
        /**
        \brief Method that executes while the service is running
        method checks for new files in directories every minute
        */
        virtual void DoWork() override;
        /**
        \method that executes once after the service is stoped
        displays a shutdown message
        \return 0
        */
        virtual int DoStop() override;
        std::shared_ptr<Watcher> p_watcher;///< class that checks for changes to a file in a directory
        std::shared_ptr<Logger> p_log;///<logger
        std::filesystem::path settingsPath;///< path to configuration file
        std::filesystem::file_time_type lastSettingTime;///< last time the settings file was changed
    };
    /**
    \brief Factory to create custom  service
    */
    class CustomServiceFactory : public ServiceLib::ServiceManagement::IServiceFactory
    {
    public:
        /**
        \service creation method
        \return an instance of the Service class
        */
        virtual std::unique_ptr<ServiceLib::ServiceManagement::Service> Create() override;

    private:
    };
}
