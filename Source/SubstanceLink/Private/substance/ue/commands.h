//! @commands.h
//! @brief Substance Link Module commands
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once
#include "SlateBasics.h"
#include "EditorStyleSet.h"
#include "Framework/Commands/UICommandList.h"

#define LOCTEXT_NAMESPACE "SubstanceLinkModule"

namespace Alg
{
namespace UE
{
class FSubstanceLinkCommands : public TCommands<FSubstanceLinkCommands>
{
public:
	TSharedPtr<FUICommandInfo> LaunchSubstanceSource;

	FSubstanceLinkCommands()
		: TCommands<FSubstanceLinkCommands>(TEXT("SubstanceLinkModuleCommands"),
											NSLOCTEXT("Contexts", "SubstanceLink", "SubstanceLink"),
											NAME_None,
											FEditorStyle::GetStyleSetName())
	{
	}

	//! @brief Function that registers the Substance Source button command
	virtual void RegisterCommands() override
	{
		UI_COMMAND(LaunchSubstanceSource, "Substance Source", "Open Substance Source", EUserInterfaceActionType::Button, FInputGesture());
	}
};

} // namespace UE
} // namespace Alg

#undef LOCTEXT_NAMESPACE