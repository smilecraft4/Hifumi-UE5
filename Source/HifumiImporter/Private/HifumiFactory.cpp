// Fill out your copyright notice in the Description page of Project Settings.


#include "HifumiFactory.h"

#include "HifumiAsset.h"
#include "HifumiLogger.h"
#include "Misc/FileHelper.h"


UHifumiFactory::UHifumiFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	bEditorImport = true;

	SupportedClass = UHifumiAsset::StaticClass();

	Formats.Add(TEXT("hla;Hifumi Line Art"));
}

UObject* UHifumiFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                           const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn,
                                           bool& bOutOperationCanceled)
{
	UHifumiAsset* HifumiAsset = NewObject<UHifumiAsset>(InParent, UHifumiAsset::StaticClass(), InName, Flags);

	if (FString FileContent; FFileHelper::LoadFileToString(FileContent, *Filename))
	{
		TArray<FString> FileLines;
		FileContent.ParseIntoArrayLines(FileLines);

		const int StrokesNum = FCString::Atoi(*FileLines[1]);

		// Allocate the number of stroke indices
		HifumiAsset->Indices.Reset();
		HifumiAsset->Indices.Reserve(StrokesNum * 2);

		int StrokeOffset = 0;
		int PointsTotalCount = 0;
		TArray<FString> StrokeLineInfo;
		for (int StrokeIndex = 0; StrokeIndex < StrokesNum; StrokeIndex++)
		{
			FileLines[2 + StrokeOffset].ParseIntoArray(StrokeLineInfo, TEXT(" "), true); // 2: point_number stroke_width
			check(StrokeLineInfo.Num() == 2);

			const int PointsNum = FCString::Atoi(*StrokeLineInfo[0]);

			HifumiAsset->Indices.Add(2 + StrokeOffset + 1); // add the start indices
			HifumiAsset->Indices.Add(2 + StrokeOffset + PointsNum); // add the end indices

			UE_LOG(LogHifumiImporter, Log, TEXT("Stroke index %i %i"), HifumiAsset->Indices[StrokeIndex * 2 + 0],
			       HifumiAsset->Indices[StrokeIndex * 2 + 1]);

			PointsTotalCount += PointsNum;
			StrokeOffset += PointsNum + 1;
		}

		UE_LOG(LogHifumiImporter, Warning, TEXT("number of indices %i"), HifumiAsset->Indices.Num());
		UE_LOG(LogHifumiImporter, Warning, TEXT("number of vertices %i"), PointsTotalCount);
		
		HifumiAsset->Vertices.Reserve(PointsTotalCount);
		
		TArray<FString> PointLineInfo;
		for (int StrokeIndex = 0; StrokeIndex < HifumiAsset->Indices.Num() / 2; StrokeIndex++)
		{
			int PointStartIndex = HifumiAsset->Indices[StrokeIndex * 2 + 0];
			int PointEndIndex = HifumiAsset->Indices[StrokeIndex * 2 + 1];

			for (int PointIndex = PointStartIndex; PointIndex < PointEndIndex + 1; PointIndex++)
			{
				FileLines[PointIndex].ParseIntoArray(PointLineInfo, TEXT(" "), true);
				check(PointLineInfo.Num() == 9);
			
				FHifumiPoint Point;
				Point.Position.X = FCString::Atod(*PointLineInfo[0]);					// forward
				Point.Position.Y = FCString::Atod(*PointLineInfo[1]);					// left
				Point.Position.Z = FCString::Atod(*PointLineInfo[2]);					// up
				Point.Position.W = FCString::Atod(*PointLineInfo[8]);					// scale
				Point.Info.X = FCString::Atod(*PointLineInfo[6]);						// size
				Point.Info.Y = FCString::Atod(*PointLineInfo[7]);						// uv

				HifumiAsset->Vertices.Add(Point);
			}
		}	
	}
	
	return HifumiAsset;
}
