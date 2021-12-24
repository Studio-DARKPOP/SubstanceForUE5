//! @file system.h
//! @brief Object implementation of the system interface
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
class LinkSystem : public LinkApplication
{
public:
	LinkSystem();
	virtual ~LinkSystem();

	//! @brief Set up the internal state for this implementation
	void initialize() override;

	//! @brief Tear down the internal state
	void shutdown() override;

	//! @brief Event handler called when a connection recevied message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	DECLARE_EVENT_TwoParams(LinkSystem, FConnectionEstablishedEvent, unsigned int, const FString&)
		FConnectionEstablishedEvent& OnConnectionEstablished()
	{
		return ConnectionEstablishedEvent;
	}

	//! @brief Event handler called when a connection closed message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	DECLARE_EVENT_TwoParams(LinkSystem, FConnectionClosedEvent, unsigned int, const FString&) FConnectionClosedEvent& OnConnectionClosed()
	{
		return ConnectionClosedEvent;
	}

private:
	//! @brief Event that is emitted when a connection recevied message is received
	FConnectionEstablishedEvent ConnectionEstablishedEvent;

	//! @brief Event that is emitted when a connection closed message is received
	FConnectionClosedEvent ConnectionClosedEvent;
};

} // namespace Qt
} // namespace Link
} // namespace Alg