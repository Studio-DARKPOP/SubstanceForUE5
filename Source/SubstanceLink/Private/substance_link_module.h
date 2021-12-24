//! @SubstanceLinkModule.h
//! @brief Substance Link Module definition
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include "ISubstanceLinkModule.h"
#include "Framework/Commands/UICommandList.h"

namespace Alg
{
namespace UE
{
class FSubstanceLinkModule : public ISubstanceLinkModule
{
public:
	//! @brief Pointer to the module commands
	TSharedPtr<FUICommandList> CommandList;

	//! @brief Initializes the substance link module
	virtual void StartupModule() override;

	//! @brief Shuts down the substance link module
	virtual void ShutdownModule() override;

private:
	//! @brief Internal pointer to the substance_link dynamic library
	void *SubstanceLinkLibrary = nullptr;

	//! @brief Internal pointer to the substance_portal_cli dynamic library
	void *SubstancePortalCliLibrary = nullptr;

	//! @brief creates the toolbar button to launch substance source in the content section
	void _create_toolbar_button();

	//! @brief callback for the substance source button click
	void onClickSubstanceSource();
};

} // namespace UE
} // namespace Alg