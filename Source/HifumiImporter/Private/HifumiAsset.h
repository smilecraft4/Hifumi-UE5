// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HifumiAsset.generated.h"

// TODO: Rearrange data structure to be more optimised for GPU usage (aligned in memory) for better indexing vbo, vao

USTRUCT(BlueprintType)
struct FHifumiPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector4 Position; // x y z + alpha
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D Info; // uv + width
};

/**
 * 
 */
UCLASS(Blueprintable)
class HIFUMIIMPORTER_API UHifumiAsset : public UObject
{
	GENERATED_BODY()

public:
	UHifumiAsset(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHifumiPoint> Vertices;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> Indices;
};
