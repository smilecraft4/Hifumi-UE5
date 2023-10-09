// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

// TODO: Is FAssetTypeActions_HifumiAsset really necessary

/**
 * 
 */
class HIFUMIIMPORTER_API FAssetTypeActions_HifumiAsset : public FAssetTypeActions_Base
{
public:
	  virtual FText GetName() const override;
	  virtual FColor GetTypeColor() const override;
	  virtual UClass* GetSupportedClass() const override;
	  virtual uint32 GetCategories() override;
};
