// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Lobotomy : ModuleRules
{
	public Lobotomy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "EngineSettings","InputCore", "EnhancedInput", "AIModule", "NavigationSystem" , "MediaAssets" , "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

                string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty"));

        string StovePCSDKPath = Path.Combine(ThirdPartyPath, "StovePCSDK");
        
        // Include 경로는 루프 바깥에서 단 한 번만 등록합니다.
        PublicIncludePaths.Add(Path.Combine(StovePCSDKPath, "Include"));

        // TODO: 게임 소유권 검증이 필요하다면 "OwnershipSDK"를 추가하고, 결제가 필요하다면 "IAPSDK"를 추가하세요.
        string[] SDKNameList = { "BaseSDK", "OwnershipSDK" };
        string Webview2LoaderDllName = "WebView2Loader.dll";
        bool IsWebviewDependencyAdded = false;

        foreach (string SDKName in SDKNameList)
        {
            // 실제 디스크 폴더인 소문자 'lib'와 'dll'을 사용하도록 수정했습니다.
            PublicAdditionalLibraries.Add(
                Path.Combine(StovePCSDKPath, "lib", "x64", SDKName + ".lib")
            );

            RuntimeDependencies.Add(
                Path.Combine("$(BinaryOutputDir)", SDKName + ".dll"),
                Path.Combine(StovePCSDKPath, "dll", "x64", SDKName + ".dll")
            );

            // Webview2Loader의 실제 경로를 'Bin' 대신 'dll'로 수정했습니다.
            if ((SDKName == "IAPSDK") && !IsWebviewDependencyAdded)
            {
                RuntimeDependencies.Add(
                    Path.Combine("$(BinaryOutputDir)", Webview2LoaderDllName),
                    Path.Combine(StovePCSDKPath, "dll", "x64", Webview2LoaderDllName)
                );
                IsWebviewDependencyAdded = true;
            }
        }

    }
}
