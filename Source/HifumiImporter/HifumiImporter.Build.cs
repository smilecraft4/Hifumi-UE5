﻿// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HifumiImporter : ModuleRules
{
	public HifumiImporter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
		
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore",
				"EditorFramework",
				"UnrealEd",
				"MainFrame",
				"PropertyEditor",
				"GeometryCache",
				"RenderCore",
				"RHI"
			}
		);
	}
}
