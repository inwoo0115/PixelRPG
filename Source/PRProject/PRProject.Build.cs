// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PRProject : ModuleRules
{
	public PRProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // 프로젝트 경로 추가
        PublicIncludePaths.Add("PRProject");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
			"EnhancedInput", "PaperZD", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG"});
	}
}
