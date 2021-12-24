//! @file component.h
//! @brief Object container of Substance Link in Unreal Engine
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include <memory>

namespace Alg
{
namespace Link
{
namespace UE
{
class Component
{
public:
	Component();

	//! @brief Initialize the Link component, starting up the Link library
	bool initialize();

	//! @brief Shuts down the Link component, starting up the Link library
	bool shutdown();

private:
	//! @brief Subclass that implements the Substance Link in Unreal Engine
	class Impl;

	//! @brief Internal pointer to the substance link implementation
	std::unique_ptr<Impl> mImpl;
};

} // namespace UE
} // namespace Link
} // namespace Alg