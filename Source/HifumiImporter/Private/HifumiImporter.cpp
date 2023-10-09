// Copyright Epic Games, Inc. All Rights Reserved.

#include "HifumiImporter.h"
#include "HifumiLogger.h"

#define LOCTEXT_NAMESPACE "FHifumiImporterModule"

DEFINE_LOG_CATEGORY(LogHifumiImporter);

void FHifumiImporterModule::StartupModule()
{
	UE_LOG(LogHifumiImporter, Warning, TEXT("Hello there, Hifumi is starting up"));
}

void FHifumiImporterModule::ShutdownModule()
{
	UE_LOG(LogHifumiImporter, Warning, TEXT("Goodbye~, Hifumi is shutding down"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHifumiImporterModule, HifumiImporter)