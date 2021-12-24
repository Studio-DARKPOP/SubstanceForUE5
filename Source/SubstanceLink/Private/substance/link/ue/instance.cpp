//! @file instance.cpp
//! @brief Unreal Engine instance of the Link Component
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/ue/instance.h"
#include "substance/link/ue/component.h"

namespace Alg
{
namespace Link
{
namespace UE
{
static std::unique_ptr<Component> moduleComponent;

void initializeInstance()
{
	moduleComponent = std::make_unique<Component>();
	moduleComponent->initialize();
}

void shutdownInstance()
{
	moduleComponent->shutdown();
	moduleComponent = nullptr;
}

} // namespace UE
} // namespace Link
} // namespace Alg