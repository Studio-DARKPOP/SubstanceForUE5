//! @file module.h
//! @brief Qt interface for the link framework
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include "Containers/UnrealString.h"

namespace Alg
{
namespace Link
{
// NOTE: namespace is Qt not because it uses qt
// but to keep the standard with the substance link code
// in all other plugins.
namespace Qt
{
class LinkApplication;

class LinkModule
{
public:
	//! @brief Query the version number of the link library
	//! @return Semantic version number as a string
	FString version() const;

	//! @brief Initialize the Link library
	//! @param applicationName FString identifier of this application
	//! @return True on success, false on failure
	bool init(const FString &applicationName);

	//! @brief Shut down the Link library
	//! @return True on success, false on failure
	bool shutdown();

	//! @brief Register an application with the core systems
	//! @param application Pointer to a LinkApplication Object
	//! @return True on success, false on failure
	bool registerApplication(LinkApplication *application);

	//! @brief Open a TCP connection at the given port
	//! @param port Integer port to open the connection at
	//! @param context Pointer to return the context through
	//! @return True on success, false on failure
	bool openTcpConnection(unsigned int port, unsigned int *context);

	//! @brief Open a default TCP connection
	//! @param context Pointer to return the context through
	//! @return True on success, false on failure
	bool openDefaultTcp(unsigned int *context);

	//! @brief Broadcast connect using tcp connections
	//! @return True on success, false on failure
	bool broadcastTcp();
};

} // namespace Qt
} // namespace Link
} // namespace Alg