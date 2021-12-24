//! @file export.h
//! @brief Object implementation of the export interface
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include "substance/link/qt/application.h"
#include "CoreMinimal.h"

namespace Alg
{
namespace Link
{
// NOTE: namespace is Qt not because it uses qt
// but to keep the standard with the substance link code
// in all other plugins.
namespace Qt
{
class LinkExport : public LinkApplication
{
public:
	LinkExport();
	virtual ~LinkExport();

	//! @brief Set up the internal state for this implementation
	void initialize() override;

	//! @brief Tear down the internal state
	void shutdown() override;

	//! @brief Event handler called when a load sbsar message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	DECLARE_EVENT_TwoParams(LinkExport, FRecvLoadSbsar, unsigned int, const FString&) FRecvLoadSbsar& OnRecvLoadSbsar()
	{
		return RecvLoadSbsarEvent;
	}

	//! @brief Event handler called when an update sbsar message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	DECLARE_EVENT_TwoParams(LinkExport, FRecvUpdateSbsar, unsigned int, const FString&) FRecvUpdateSbsar& OnRecvUpdateSbsar()
	{
		return RecvUpdateSbsarEvent;
	}

private:
	//! @brief Event that is emitted when a load sbsar message is received
	FRecvLoadSbsar RecvLoadSbsarEvent;

	//! @brief Event that is emitted when an update sbsar message is received
	FRecvUpdateSbsar RecvUpdateSbsarEvent;
};

} // namespace Qt
} // namespace Link
} // namespace Alg