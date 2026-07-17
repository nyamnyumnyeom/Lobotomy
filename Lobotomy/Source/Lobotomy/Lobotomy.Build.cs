// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Lobotomy : ModuleRules
{
    public Lobotomy(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "EngineSettings",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "NavigationSystem",
            "MediaAssets",
            "Slate",
            "SlateCore",
            "OnlineSubsystem",
            "OnlineSubsystemUtils"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "OnlineSubsystemSteam",
            "Steamworks"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        // ---------------------------------------------------------------------
        // Stove PCSDK 설정
        // ---------------------------------------------------------------------
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
            // 실제 디스크 폴더인 소문자 'lib'와 'dll' 사용
            PublicAdditionalLibraries.Add(
                Path.Combine(StovePCSDKPath, "lib", "x64", SDKName + ".lib")
            );

            RuntimeDependencies.Add(
                Path.Combine("$(BinaryOutputDir)", SDKName + ".dll"),
                Path.Combine(StovePCSDKPath, "dll", "x64", SDKName + ".dll")
            );

            // Webview2Loader의 실제 경로를 'dll'로 수정
            if ((SDKName == "IAPSDK") && !IsWebviewDependencyAdded)
            {
                RuntimeDependencies.Add(
                    Path.Combine("$(BinaryOutputDir)", Webview2LoaderDllName),
                    Path.Combine(StovePCSDKPath, "dll", "x64", Webview2LoaderDllName)
                );
                IsWebviewDependencyAdded = true;
            }
        }

        // Stove Signature Verifier 보안 강화 정적 라이브러리 링크 추가
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "StoveSignatureVerifier.lib"));

        // ---------------------------------------------------------------------
        // Steamworks SDK - Encrypted App Ticket 연동 설정
        // ---------------------------------------------------------------------
        string SteamworksSDKPath = Path.Combine(ThirdPartyPath, "steamworks_sdk_164");
        PublicIncludePaths.Add(Path.Combine(SteamworksSDKPath, "sdk", "public", "steam"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string SteamLibPath = Path.Combine(SteamworksSDKPath, "sdk", "public", "steam", "lib", "win64");

            // sdkencryptedappticket64.lib 정적 라이브러리 링크
            PublicAdditionalLibraries.Add(Path.Combine(SteamLibPath, "sdkencryptedappticket64.lib"));

            // sdkencryptedappticket64.dll 런타임 종속성 추가 (Binaries 폴더 복사)
            RuntimeDependencies.Add(
                Path.Combine("$(BinaryOutputDir)", "sdkencryptedappticket64.dll"),
                Path.Combine(SteamLibPath, "sdkencryptedappticket64.dll")
            );
        }
    }
}