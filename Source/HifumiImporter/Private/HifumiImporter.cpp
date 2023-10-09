// Copyright Epic Games, Inc. All Rights Reserved.

#include "HifumiImporter.h"

#include "AssetToolsModule.h"
#include "FAssetTypeActions_HifumiAsset.h"
#include "HifumiAsset.h"
#include "HifumiFactory.h"
#include "HifumiLogger.h"
#include "IAssetTools.h"
#include "AssetRegistryModule.h"

#define LOCTEXT_NAMESPACE "FHifumiImporterModule"

DEFINE_LOG_CATEGORY(LogHifumiImporter);


// TODO: Clean up any unnecessary steps
void FHifumiImporterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogHifumiImporter, Warning, TEXT("Hello there, Hifumi is starting up"));
	
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	IAssetRegistry& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TSharedRef<IAssetTypeActions> HifumiAssetAction = TSharedRef<IAssetTypeActions>(new FAssetTypeActions_HifumiAsset);
	AssetTools.RegisterAssetTypeActions(HifumiAssetAction);

	TArray<FAssetData> AssetData;
	AssetRegistryModule.GetAssetsByClass(UHifumiAsset::StaticClass()->GetFName(), AssetData);

	for (const FAssetData& Data : AssetData)
	{
		UE_LOG(LogHifumiImporter, Warning, TEXT("Found registered asset: %s"), *Data.AssetName.ToString());
	}
}

void FHifumiImporterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogHifumiImporter, Warning, TEXT("Goodbye~, Hifumi is shutding down"));

	
	// if(UObjectInitialized())
	// {
	// 	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	// 	AssetTools.UnregisterAssetTypeActions(new MakeShared<UHifumiFactory>());
	// }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHifumiImporterModule, HifumiImporter)