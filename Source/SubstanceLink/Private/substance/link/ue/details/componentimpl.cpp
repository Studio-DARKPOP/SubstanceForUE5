//! @file componentimpl.cpp
//! @brief Implementation of Substance Link in Unreal Engine
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

#include "substance/link/ue/details/componentimpl.h"
#include "substance/link/ue/component.h"
#include "substance/link/qt/export.h"
#include "substance/link/qt/module.h"
#include "substance/link/qt/system.h"
#include <CoreMinimal.h>
#include "ContentBrowserModule.h"
#include "AssetToolsModule.h"
#include "SubstanceFactory.h"
#include "Async/Async.h"

namespace Alg
{
namespace Link
{
namespace UE
{
static const char* const linkApplicationName = "Unreal Engine";

Component::Impl::Impl()
	: mContentBrowserPath("/Game")
	, mLinkModule(new Qt::LinkModule)
	, mLinkExport(new Qt::LinkExport)
	, mLinkSystem(new Qt::LinkSystem)
	, mOpenContext(0u)
{
	mLinkExport->initialize();
	mLinkSystem->initialize();
	mLinkModule->registerApplication(mLinkExport.get());
	mLinkModule->registerApplication(mLinkSystem.get());

	mLinkSystem->OnConnectionEstablished().AddRaw(this, &Component::Impl::onRecvConnectionEstablished);
	mLinkSystem->OnConnectionClosed().AddRaw(this, &Component::Impl::onRecvConnectionClosed);

	mLinkExport->OnRecvLoadSbsar().AddRaw(this, &Component::Impl::onRecvLoadSbsar);
	mLinkExport->OnRecvUpdateSbsar().AddRaw(this, &Component::Impl::onRecvUpdateSbsar);

	FString app_name(linkApplicationName);
	mLinkModule->init(app_name);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FContentBrowserModule::FOnAssetPathChanged& PathChangedDelegate = ContentBrowserModule.GetOnAssetPathChanged();
	PathChangedDelegate.AddRaw(this, &Component::Impl::OnContentBrowserPathChanged);
}

bool Component::Component::Impl::initialize()
{
	bool result = mLinkModule->openDefaultTcp(&mOpenContext);

	if (result)
	{
		result = mLinkModule->broadcastTcp();
	}
	return result;
}

bool Component::Impl::shutdown()
{
	// mLinkSystem->shutdown();
	// mLinkExport->shutdown();
	return mLinkModule->shutdown();
}

void Component::Impl::onRecvConnectionEstablished(unsigned int context, const FString& message)
{
	UE_LOG(LogSubstanceLink, Warning, TEXT("Connection established: %s"), *message);
}

void Component::Impl::onRecvConnectionClosed(unsigned int context, const FString& message)
{
	UE_LOG(LogSubstanceLink, Warning, TEXT("Connection closed: %s"), *message);
}

void Component::Impl::onRecvLoadSbsar(unsigned int context, const FString& message)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

		USubstanceFactory::SuppressImportOverwriteDialog();

		TArray<FString> SourcePaths;
		SourcePaths.Add(message);

		UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>();
		ImportData->bReplaceExisting = true;
		ImportData->Filenames = SourcePaths;
		ImportData->DestinationPath = mContentBrowserPath;
		ImportData->bSkipReadOnly = true;
		AssetToolsModule.Get().ImportAssetsAutomated(ImportData);

		UE_LOG(LogSubstanceLink, Warning, TEXT("Import Sbsar: %s"), *message);
	});
}

void Component::Impl::onRecvUpdateSbsar(unsigned int context, const FString& message)
{
	UE_LOG(LogSubstanceLink, Warning, TEXT("Update Sbsar: %s"), *message);
}

void Component::Impl::OnContentBrowserPathChanged(const FString& Path)
{
	mContentBrowserPath = Path;
}

} // namespace UE
} // namespace Link
} // namespace Alg