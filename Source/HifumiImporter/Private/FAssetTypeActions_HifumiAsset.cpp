// Fill out your copyright notice in the Description page of Project Settings.


#include "FAssetTypeActions_HifumiAsset.h"
#include "HifumiAsset.h"

FText FAssetTypeActions_HifumiAsset::GetName() const
{
	return FText::FromString(TEXT("Hifumi Line Art"));
}

FColor FAssetTypeActions_HifumiAsset::GetTypeColor() const
{
	return FColor(128, 128, 128);
}

UClass* FAssetTypeActions_HifumiAsset::GetSupportedClass() const
{
	return UHifumiAsset::StaticClass();
}

uint32 FAssetTypeActions_HifumiAsset::GetCategories()
{
	return 1;
}
