// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyFirstRPG : ModuleRules
{
	public MyFirstRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "SlateCore" });

		PrivateIncludePaths.Add("MyFirstRPG");
		PublicIncludePaths.Add("MyFirstRPG");
	}
}
