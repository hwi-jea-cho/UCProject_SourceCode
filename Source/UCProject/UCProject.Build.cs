// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UCProject : ModuleRules
{
	public UCProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"SlateCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
