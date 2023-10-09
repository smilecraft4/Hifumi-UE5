// Fill out your copyright notice in the Description page of Project Settings.


#include "HifumiAsset.h"
#include "HifumiLogger.h"

UHifumiAsset::UHifumiAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHifumiAsset::UHifumiAsset(const FString& Name, const FString& SourceFile)
{
	this->Name = Name;
	this->SourceHifumiFile = SourceFile;

	UE_LOG(LogHifumiImporter, Warning, TEXT("Manual creation of HifumiAsset"));
}
