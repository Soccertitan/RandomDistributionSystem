// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RandomDistributionSystem : ModuleRules
{
	public RandomDistributionSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CoreUObject", 
				"GameplayTags",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine", 
				"AIModule",
			}
			);
	}
}
