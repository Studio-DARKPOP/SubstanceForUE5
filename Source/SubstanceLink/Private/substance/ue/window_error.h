//! @window_error.h
//! @brief Substance Source not found dialog window
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Images/SImage.h"

namespace Alg
{
namespace UE
{
class WindowError : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(WindowError)
	{
	}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainHUD>, OwnerHUD)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void OnOpenHyperlink(FString LinkName);

	TWeakObjectPtr<class AMainHUD> OwnerHUD;
};

} // namespace UE
} // namespace Alg
