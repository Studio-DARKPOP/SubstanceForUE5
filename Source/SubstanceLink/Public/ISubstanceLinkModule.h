//! @ISubstanceLinkModule.h
//! @brief Substance Link Module definition interface
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>

namespace Alg
{
namespace UE
{
class ISubstanceLinkModule : public IModuleInterface
{
public:
	//! @brief Static method to get the module instance
	static ISubstanceLinkModule* Get();
};

} // namespace UE
} // namespace Alg