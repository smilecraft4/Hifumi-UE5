// Fill out your copyright notice in the Description page of Project Settings.


#include "HifumiFactory.h"
#include "HifumiAsset.h"
#include "HifumiLogger.h"
#include "Misc/FileHelper.h"



UHifumiFactory::UHifumiFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogHifumiImporter, Log, TEXT("UHifumiFactory::UHifumiFactory"));
	Formats.Add(TEXT("hla;Hifumi Line Art"));
	SupportedClass = UHifumiAsset::StaticClass();
	
	bCreateNew = false;
	bEditorImport = true;
}

UObject* UHifumiFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{	
	UHifumiAsset* HifumiAsset = NewObject<UHifumiAsset>(InParent, UHifumiAsset::StaticClass(), FName("Example"), Flags);
	if(!HifumiAsset)
	{
		UE_LOG(LogHifumiImporter, Error, TEXT("Failed to create an HifumiAsset"));
		return nullptr;
	}

	FString FileContent;

	/** Structure of .hla files
	 * 0: file_type version
	 * 1: stroke_number
	 * 2: point_number stroke_width
	 * 3: x y z r g b alpha uv size
	 * 4: point_number stroke_width
	 * 5: x y z r g b alpha uv size
	 * 6: x y z r g b alpha uv size
	 * 7: x y z r g b alpha uv size
	 * 8: point_number stroke_width
	 * 9: x y z r g b alpha uv size
	 */

	// TODO: Create a function for this
	// TODO: Implement Tracing for checking performances
	if(FFileHelper::LoadFileToString(FileContent, *Filename))
	{
		int Progress = 0;
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines);

		if(Lines.Num() < 2)
		{
			UE_LOG(LogHifumiImporter, Error, TEXT("Hifumi Line Art File is incorrect (missing stroke information)"));
			return nullptr;
		}

		int LineCount = 0;
		for (const FString& Line: Lines)
		{
			UE_LOG(LogHifumiImporter, Log, TEXT("%i: %s"), LineCount, *Line);
			LineCount++;
		}
		
		int32 StrokesNum = FCString::Atoi(*Lines[1]); // 1: stroke_number
		Progress++;
		if(StrokesNum == 0)
		{
			UE_LOG(LogHifumiImporter, Warning, TEXT("No strokes found in file"));
			return nullptr;
		}
		if(StrokesNum > 1000)
		{
			UE_LOG(LogHifumiImporter, Error, TEXT("Too many strokes in file, Only importing 100 of them"));
			StrokesNum = 1000;
		}
		
		TArray<FHifumiStroke> Strokes;
		Strokes.Reserve(StrokesNum);

		TArray<FString> StrokeInfo;
		int StrokeOffset = 0;
		for (int StrokeIndex = 0; StrokeIndex < StrokesNum; StrokeIndex++)
		{
			Lines[2 + StrokeOffset].ParseIntoArray(StrokeInfo, TEXT(" "), true); // 2: point_number stroke_width
			Progress++;
			if(StrokeInfo.Num() != 2)
			{
				int Offset = 2 + StrokeOffset + 1;
				UE_LOG(LogHifumiImporter, Error, TEXT("Wrong info %i, Progress:%i, Offset:%i"), StrokeInfo.Num(), Progress, Offset);
				return nullptr;
			}
			
			int32 PointsNum = FCString::Atoi(*StrokeInfo[0]);
			int32 StrokeWidth = FCString::Atoi(*StrokeInfo[0]);
			
			FHifumiStroke CurrentStroke{};
			CurrentStroke.Width = StrokeWidth;
			CurrentStroke.Points.Reserve(PointsNum);

			TArray<FString> PointData;
			for (int PointIndex = 0; PointIndex < PointsNum; ++PointIndex)
			{
				int PointOffset = 2 + StrokeOffset + 1 + PointIndex;
				Lines[PointOffset].ParseIntoArray(PointData, TEXT(" "), true); // 3: x y z r g b alpha uv size
				Progress++;

				if(PointData.Num() != 9)
				{
					UE_LOG(LogHifumiImporter, Verbose, TEXT("Skipping point because of incorrect number of data"));
					break;
				}
				
				FHifumiPoint CurrentPoint{};
				CurrentPoint.Location.X = FCString::Atod(*PointData[0]);
				CurrentPoint.Location.Y = FCString::Atod(*PointData[1]);
				CurrentPoint.Location.Z = FCString::Atod(*PointData[2]);
				CurrentPoint.Color.X = FCString::Atod(*PointData[3]);
				CurrentPoint.Color.Y = FCString::Atod(*PointData[4]);
				CurrentPoint.Color.Z = FCString::Atod(*PointData[5]);
				CurrentPoint.Opacity = FCString::Atod(*PointData[6]);
				CurrentPoint.UV = FCString::Atod(*PointData[7]);
				CurrentPoint.Size = FCString::Atod(*PointData[8]);

				CurrentStroke.Points.Add(CurrentPoint);
			}
			StrokeOffset += PointsNum + 1;

			HifumiAsset->Strokes.Add(CurrentStroke);
		}
		

		return  HifumiAsset;
	}

	// Read line by line n:0
	// First line is the header n:1
	//			line n:3+i+j is the stroke at index j
	//				each line is composed of double in order xyz,rgb,a,s,a each seperated by spaces
	//			this goes on until j is at the max
	
	// ignore the 1 because it is an single point stroke
	
	// Generate Dummy data
	FHifumiPoint DummyPoint1 = FHifumiPoint();
	DummyPoint1.Location = FVector3d(12.0, 5.0, 4.0);
	
	TArray<FHifumiPoint> DummyPoints = {};
	DummyPoints.Add(DummyPoint1);
	
	TArray<FHifumiStroke> DummyStrokes = {};
	DummyStrokes.Add(FHifumiStroke(DummyPoints));
	
	HifumiAsset->Strokes = DummyStrokes;
	HifumiAsset->SourceHifumiFile = Filename;
	HifumiAsset->Name = TEXT("Test");
	
	return HifumiAsset;
}
