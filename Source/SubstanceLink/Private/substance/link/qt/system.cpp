//! @file system.cpp
//! @brief Object implementation of the system interface
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/qt/system.h"

#include <atomic>
#include "CoreMinimal.h"

#include <substance/link/framework/system.h>

namespace Alg
{
namespace Link
{
namespace Qt
{
static std::atomic<LinkSystem *> systemInstance(nullptr);

static void recvConnectionEstablishedCallback(unsigned int context, const substance_link_uuid_t *uuid, const char *message)
{
	if (systemInstance.load() != nullptr)
	{
		FString msg(message);
		systemInstance.load()->OnConnectionEstablished().Broadcast(context, msg);
	}
}

static void recvConnectionClosedCallback(unsigned int context, const substance_link_uuid_t *uuid, const char *message)
{
	if (systemInstance.load() != nullptr)
	{
		FString msg(message);
		systemInstance.load()->OnConnectionClosed().Broadcast(context, msg);
	}
}

LinkSystem::LinkSystem() : LinkApplication()
{
}

LinkSystem::~LinkSystem()
{
}

void LinkSystem::initialize()
{
	LinkSystem *expected = nullptr;

	// Only a single instance should be valid
	if (systemInstance.compare_exchange_strong(expected, this))
	{
		// Instantiate a new instance of the base framework system
		// application type
		mApplication = std::make_unique<Framework::System>();

		Framework::System *systemApplication = static_cast<Framework::System *>(mApplication.get());

		// Update the callback pointers
		systemApplication->mRecvConnectionEstablished = recvConnectionEstablishedCallback;
		systemApplication->mRecvConnectionClosed = recvConnectionClosedCallback;

		ConnectionEstablishedEvent.Clear();
		ConnectionClosedEvent.Clear();
	}
}

void LinkSystem::shutdown()
{
	if (systemInstance.load() == this)
	{
		// ConnectionEstablishedEvent.Clear();
		// ConnectionClosedEvent.Clear();

		mApplication = nullptr;

		// Only clear the atomic pointer after the shutdown has been completed
		LinkSystem *expected = this;
		systemInstance.compare_exchange_strong(expected, nullptr);
	}
}

} // namespace Qt
} // namespace Link
} // namespace Alg