//! @window_error.cpp
//! @brief Substance Source not found dialog window
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/ue/window_error.h"

#include "substance/ue/style.h"

#define LOCTEXT_NAMESPACE "SubstanceLinkModule"

namespace Alg
{
namespace UE
{
void WindowError::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	ChildSlot.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)[SNew(SOverlay) +
							 SOverlay::Slot()
								 .HAlign(HAlign_Center)
								 .VAlign(VAlign_Center)
									 [SNew(SVerticalBox) +
									  SVerticalBox::Slot()
										  .Padding(10.0f)
										  .HAlign(HAlign_Center)
										  .VAlign(VAlign_Center)
										  .AutoHeight()[SNew(SImage).Image(FSubstanceLinkStyle::Get()->GetBrush("SubstanceLinkButtonIcon.Large"))] +
									  SVerticalBox::Slot()
										  .Padding(10.0f)
										  .HAlign(HAlign_Center)
										  .VAlign(VAlign_Center)
										  .AutoHeight()[SNew(STextBlock)
															.ShadowColorAndOpacity(FLinearColor::Black)
															.ColorAndOpacity(FLinearColor::White)
															.ShadowOffset(FIntPoint(-1, 1))
															.Justification(ETextJustify::Center)
															.Text(LOCTEXT("SubstanceSourceNotFound",
																		  "Substance Launcher not found,\nplease download it from the website"))] +
									  SVerticalBox::Slot()
										  .Padding(10.0f)
										  .HAlign(HAlign_Center)
										  .VAlign(VAlign_Center)
											  [SNew(SHyperlink)
												   .Text(FText::FromString("Get Substance Launcher"))
												   .OnNavigate(this, &WindowError::OnOpenHyperlink, FString("https://www.substance3d.com/launcher"))]

	]

	];
}

void WindowError::OnOpenHyperlink(FString LinkName)
{
	FPlatformProcess::LaunchURL(*LinkName, nullptr, nullptr);
}

} // namespace UE
} // namespace Alg

#undef LOCTEXT_NAMESPACE