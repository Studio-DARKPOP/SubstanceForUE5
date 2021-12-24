//! @file application.h
//! @brief Object implementation of an application object
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include <memory>

namespace Alg
{
namespace Link
{
namespace Framework
{
class Application;
} // namespace Framework

// NOTE: namespace is Qt not because it uses qt
// but to keep the standard with the substance link code
// in all other plugins.
namespace Qt
{
class LinkApplication
{
public:
	LinkApplication();
	virtual ~LinkApplication();

	//! @brief Setup the application's initial state
	virtual void initialize() = 0;

	//! @brief Close the application's state on shutdown
	virtual void shutdown() = 0;

protected:
	//! @brief Internal pointer to the application
	std::unique_ptr<Framework::Application> mApplication;

	friend class LinkModule;
};

} // namespace Qt
} // namespace Link
} // namespace Alg