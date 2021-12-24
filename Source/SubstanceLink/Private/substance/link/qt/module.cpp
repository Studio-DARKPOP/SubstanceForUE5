//! @file module.cpp
//! @brief Qt interface for the link framework
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/qt/module.h"

#include <string>
#include <CoreMinimal.h>

#include "substance/link/qt/application.h"
#include <substance/link/link.h>
#include <substance/link/errorcodes.h>
#include <substance/link/framework/core.h>
#include <substance/link/framework/application.h>

namespace Alg
{
namespace Link
{
namespace Qt
{
FString LinkModule::version() const
{
	return FString(substance_link_version());
}

bool LinkModule::init(const FString& applicationName)
{
	std::string name = std::string(TCHAR_TO_UTF8(*applicationName));
	return Framework::init(name);
}

bool LinkModule::shutdown()
{
	return Framework::shutdown();
}

bool LinkModule::registerApplication(LinkApplication* application)
{
	return Framework::registerApplication(application->mApplication.get());
}

bool LinkModule::openTcpConnection(unsigned int port, unsigned int* context)
{
	return Framework::openTcpConnection(port, context);
}

bool LinkModule::openDefaultTcp(unsigned int* context)
{
	return Framework::openDefaultTcp(context);
}

bool LinkModule::broadcastTcp()
{
	return Framework::broadcastTcp();
}

} // namespace Qt
} // namespace Link
} // namespace Alg