//! @file component.cpp
//! @brief Object container of Substance Link in Unreal Engine
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/ue/component.h"
#include "substance/link/ue/details/componentimpl.h"

namespace Alg
{
namespace Link
{
namespace UE
{
Component::Component() : mImpl(new Impl)
{
}

bool Component::initialize()
{
	return mImpl->initialize();
}

bool Component::shutdown()
{
	return mImpl->shutdown();
}

} // namespace UE
} // namespace Link
} // namespace Alg