//! @file componentimpl.h
//! @brief Implementation of Substance Link in Unreal Engine
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include "Containers/UnrealString.h"
#include "substance/link/ue/component.h"

namespace Alg
{
namespace Link
{
namespace Qt
{
class LinkModule;
class LinkExport;
class LinkSystem;
} // namespace Qt

namespace UE
{
class Component::Impl
{
public:
	Impl();

	//! @brief Initialize the substance link implementation
	bool initialize();

	//! @brief Shuts down the substance link implementation
	bool shutdown();

	//! @brief Function to be called when a new connection message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	void onRecvConnectionEstablished(unsigned int context, const FString& message);

	//! @brief Function to be called when a connection closed message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	void onRecvConnectionClosed(unsigned int context, const FString& message);

	//! @brief Function to be called when a load sbsar message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	void onRecvLoadSbsar(unsigned int context, const FString& message);

	//! @brief Function to be called when an update sbsar message is received
	//! @param context Integer representing the underlying connection
	//! @param message FString value of the received message
	void onRecvUpdateSbsar(unsigned int context, const FString& message);

private:
	void OnContentBrowserPathChanged(const FString& Path);

	FString mContentBrowserPath;

	//! @brief Internal pointer to the module interface of the substance link
	std::unique_ptr<Qt::LinkModule> mLinkModule;

	//! @brief Internal pointer to the export module of the substance link
	std::unique_ptr<Qt::LinkExport> mLinkExport;

	//! @brief Internal pointer to the system module of the substance link
	std::unique_ptr<Qt::LinkSystem> mLinkSystem;

	//! @brief Integer representing the current context for the substance link
	unsigned int mOpenContext;
};

} // namespace UE
} // namespace Link
} // namespace Alg