//! @file export.cpp
//! @brief Object implementation of the export interface
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/qt/export.h"

#include <atomic>
#include <CoreMinimal.h>

#include <substance/link/framework/export.h>

namespace Alg
{
namespace Link
{
namespace Qt
{
static std::atomic<LinkExport *> exportInstance(nullptr);

static void recvLoadSbsarCallback(unsigned int context, const substance_link_uuid_t *uuid, const char *message)
{
	if (exportInstance.load() != nullptr)
	{
		FString msg(message);
		exportInstance.load()->OnRecvLoadSbsar().Broadcast(context, msg);
	}
}

static void recvUpdateSbsarCallback(unsigned int context, const substance_link_uuid_t *uuid, const char *message)
{
	if (exportInstance.load() != nullptr)
	{
		FString msg(message);
		exportInstance.load()->OnRecvUpdateSbsar().Broadcast(context, msg);
	}
}

LinkExport::LinkExport() : LinkApplication()
{
}

LinkExport::~LinkExport()
{
}

void LinkExport::initialize()
{
	LinkExport *expected = nullptr;

	if (exportInstance.compare_exchange_strong(expected, this))
	{
		mApplication = std::make_unique<Framework::Export>();

		Framework::Export *exportApplication = static_cast<Framework::Export *>(mApplication.get());

		exportApplication->mRecvLoadSbsar = recvLoadSbsarCallback;
		exportApplication->mRecvUpdateSbsar = recvUpdateSbsarCallback;

		RecvLoadSbsarEvent.Clear();
		RecvUpdateSbsarEvent.Clear();
	}
}

void LinkExport::shutdown()
{
	if (exportInstance.load() == this)
	{
		RecvLoadSbsarEvent.Clear();
		RecvUpdateSbsarEvent.Clear();

		mApplication = nullptr;

		LinkExport *expected = this;
		exportInstance.compare_exchange_strong(expected, nullptr);
	}
}

} // namespace Qt
} // namespace Link
} // namespace Alg