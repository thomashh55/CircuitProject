// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "INewtonPlugin.h"


class FNewtonPlugin : public INewtonPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FNewtonPlugin, NewtonPlugin )



void FNewtonPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FNewtonPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



