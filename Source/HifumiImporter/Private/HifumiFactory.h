// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"
#include "HifumiFactory.generated.h"


// TODO: Implement reimport

/**
 * 
 */
UCLASS()
class HIFUMIIMPORTER_API UHifumiFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
		const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
