//! @file instance.h
//! @brief Unreal Engine instance of the Link Component
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

namespace Alg
{
namespace Link
{
namespace UE
{
//! @brief Initialize the Link instance, starting up the Link library
void initializeInstance();

//! @brief Perform a shutdown of the Link instance, shutting down the Link library
void shutdownInstance();

} // namespace UE
} // namespace Link
} // namespace Alg