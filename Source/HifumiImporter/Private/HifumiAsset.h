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
	FHifumiPoint() : Location(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), Opacity(1.0), Size(1.0), UV(0.0)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Location;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Color;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Opacity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Size;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float UV;
};

USTRUCT(BlueprintType)
struct FHifumiStroke
{
	GENERATED_BODY()

public:
	FHifumiStroke() = default;	
	FHifumiStroke(const TArray<FHifumiPoint>& Points): Width(1.0), Points(Points)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Width;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHifumiPoint> Points;
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
	UHifumiAsset(const FString& Name, const FString& SourceFile);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SourceHifumiFile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHifumiStroke> Strokes;
};
