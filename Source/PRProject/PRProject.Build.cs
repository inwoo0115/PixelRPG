// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PRProject : ModuleRules
{
	public PRProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // ������Ʈ ��� �߰�
        PublicIncludePaths.Add("PRProject");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
			"EnhancedInput", "PaperZD", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG"});
	}
}
