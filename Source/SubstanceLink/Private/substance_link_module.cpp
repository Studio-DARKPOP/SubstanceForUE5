//! @SubstanceLinkModule.cpp
//! @brief Substance Link Module definition
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance_link_module.h"

#include <Modules/ModuleManager.h>
#include <Interfaces/IPluginManager.h>
#include <LevelEditor.h>
#include <Misc/MessageDialog.h>
#include "Interfaces/IMainFrameModule.h"

#include <substance/portal/cli/cli.h>
#include "substance/link/ue/instance.h"
#include "substance/ue/style.h"
#include "substance/ue/commands.h"
#include "substance/ue/window_error.h"

// Resolve library file name depending on build platform
#if defined(SUBSTANCE_LINK_DEBUG)
#define SUBSTANCE_LINK_LIB_CONFIG "Debug"
#else
#define SUBSTANCE_LINK_LIB_CONFIG "Release"
#endif

#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
#define SUBSTANCE_LINK_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Win64/substance_link.dll")
#define SUBSTANCE_PORTAL_CLI_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Win64/substance_portal_cli.dll")
#else
#error Unsupported platform for dynamic substance loading
#endif
#elif PLATFORM_MAC
#define SUBSTANCE_LINK_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Mac/libsubstance_link.dylib")
#define SUBSTANCE_PORTAL_CLI_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Mac/substance_portal_cli.dylib")
#elif PLATFORM_LINUX
#define SUBSTANCE_LINK_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Linux/libsubstance_link.so")
#define SUBSTANCE_PORTAL_CLI_DLL_PATH TEXT("/DLLs/" SUBSTANCE_LINK_LIB_CONFIG "/Linux/substance_portal_cli.so")
#else
#error Unsupported platform for dynamic substance loading
#endif

#define LOCTEXT_NAMESPACE "SubstanceLinkModule"

namespace Alg
{
namespace UE
{
void FSubstanceLinkModule::StartupModule()
{
	// Initialize Style
	FSubstanceLinkStyle::Initialize();

	FString RootPath = IPluginManager::Get().FindPlugin("Substance")->GetBaseDir();
	// Delay Load Substance Link Dynamic Library
	FString SubstanceLinkPath = RootPath + SUBSTANCE_LINK_DLL_PATH;
	SubstanceLinkLibrary = FPlatformProcess::GetDllHandle(*SubstanceLinkPath);
	// Delay Load Substance Portal Cli Dynamic Library
	FString SubstancePortalCliPath = RootPath + SUBSTANCE_PORTAL_CLI_DLL_PATH;
	SubstancePortalCliLibrary = FPlatformProcess::GetDllHandle(*SubstancePortalCliPath);

	// Initialize Substance Link
	Alg::Link::UE::initializeInstance();

	// Register Module Commands
	FSubstanceLinkCommands::Register();
	CommandList = MakeShareable(new FUICommandList);

	// Add toolbar button
	_create_toolbar_button();
}

void FSubstanceLinkModule::ShutdownModule()
{
	// Shutdown Substance Link
	Alg::Link::UE::shutdownInstance();

	// Shutdown style
	FSubstanceLinkStyle::Shutdown();

	// Unload Substance Link DLL
	if (SubstanceLinkLibrary != nullptr)
		FPlatformProcess::FreeDllHandle(SubstanceLinkLibrary);
	SubstanceLinkLibrary = nullptr;
	// Unload Substance Portal Cli DLL
	if (SubstancePortalCliLibrary != nullptr)
		FPlatformProcess::FreeDllHandle(SubstancePortalCliLibrary);
	SubstancePortalCliLibrary = nullptr;
}

void FSubstanceLinkModule::_create_toolbar_button()
{
	// Create Toolbar button action
	CommandList->MapAction(FSubstanceLinkCommands::Get().LaunchSubstanceSource,
						   FExecuteAction::CreateRaw(this, &FSubstanceLinkModule::onClickSubstanceSource));

	struct Local
	{
		static void AddToolbarCommands(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.AddToolBarButton(FSubstanceLinkCommands::Get().LaunchSubstanceSource,
											NAME_None,
											FText::FromString("Source"),
											FText::FromString("Substance Source"),
											FSlateIcon("SubstanceLinkStyle", "SubstanceLinkButtonIcon"));
		}
	};

	// Create Toolbar button
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension(
		"Content", EExtensionHook::After, CommandList, FToolBarExtensionDelegate::CreateStatic(&Local::AddToolbarCommands));
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FSubstanceLinkModule::onClickSubstanceSource()
{
	if (substance_portal_cli_invoke() == 0)
	{
		UE_LOG(LogSubstanceLink, Warning, TEXT("Substance Launcher found"));
	}
	else
	{
		TSharedPtr<SWindow> ParentWindow;
		IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
		ParentWindow = MainFrame.GetParentWindow();

		TSharedRef<SWindow> Window =
			SNew(SWindow).Title(NSLOCTEXT("UnrealEd", "SubstanceSourceFailed", "Substance Source")).SizingRule(ESizingRule::Autosized);

		TSharedPtr<WindowError> SubstanceErrorWindow;
		Window->SetContent(SAssignNew(SubstanceErrorWindow, WindowError));

		FSlateApplication::Get().AddModalWindow(Window, ParentWindow, false);

		UE_LOG(LogSubstanceLink, Warning, TEXT("Substance Launcher not found"));
	}
}

ISubstanceLinkModule* ISubstanceLinkModule::Get()
{
	return &FModuleManager::LoadModuleChecked<FSubstanceLinkModule>("SubstanceLink");
}

} // namespace UE
} // namespace Alg

// Actual definition of the unreal engine plugin module
IMPLEMENT_MODULE(Alg::UE::FSubstanceLinkModule, SubstanceLink);

#undef LOCTEXT_NAMESPACE