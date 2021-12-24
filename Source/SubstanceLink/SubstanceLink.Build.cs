//! @SubstanceLink.Build.cs
//! @brief UE4 Plugin Module builder
//! @author Ymmanuel Flores - Adobe
//! @date 20193009
//! @copyright Adobe. All rights reserved.

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class SubstanceLink : ModuleRules
{
    private string _pluginRootPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../")); }
    }

    private string _substanceIncludePath
    {
        get { return Path.GetFullPath(Path.Combine(_pluginRootPath, "Include")); }
    }

    public SubstanceLink(ReadOnlyTargetRules Target) : base(Target)
    {
        //Deinfe the PCH file
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;
        PrivatePCHHeaderFile = "Private/SubstanceLinkPrivatePCH.h";

        //Set the Include Paths
        PrivateIncludePaths.AddRange(new string[] {
            "SubstanceLink/Private",
            _substanceIncludePath
        });


        //Set the Module Dependencies
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "UnrealEd",
            "SubstanceEditor"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Projects",
            "InputCore",
            "SlateCore",
            "PropertyEditor",
            "LevelEditor",
            "EditorStyle",
            "SubstanceEditor"
        });

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            //Define External DLLs
            PublicDelayLoadDLLs.Add(_getDllName(Target, "substance_link"));
            PublicDelayLoadDLLs.Add(_getDllName(Target, "substance_portal_cli"));
        }
        //Define External Libs
        PublicAdditionalLibraries.Add(Path.Combine(_getLibPath(Target), _getLibName(Target, "substance_link")));
        PublicAdditionalLibraries.Add(Path.Combine(_getLibPath(Target), _getLibName(Target, "substance_portal_cli")));
        PublicAdditionalLibraries.Add(Path.Combine(_getLibPath(Target), _getLibName(Target, "substancelink_framework")));
        

        //Add Compile Definitions
        string BuildConfig = _getBuildConfig(Target);
        if (BuildConfig == "Debug")
            PublicDefinitions.Add("SUBSTANCE_LINK_DEBUG");


    }

    public string _getBuildConfig(ReadOnlyTargetRules Target)
    {
        string BuildConfig = "Release";
        if (Target.Configuration == UnrealTargetConfiguration.Debug)
        {
            BuildConfig = "Debug";
        }
        return BuildConfig;
    }

    public string _getLibPath(ReadOnlyTargetRules Target)
    {
        string BuildConfig = _getBuildConfig(Target);
        string PlatformConfig = Target.Platform.ToString();

        return Path.GetFullPath(Path.Combine(_pluginRootPath, "Libs/" + BuildConfig + "/" + PlatformConfig + "/"));
    }

    public string _getLibName(ReadOnlyTargetRules Target, string lib)
    {
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            return lib + ".lib";
        }
        else
        {
            return "lib" + lib + ".a";
        }
    }

    public string _getDllName(ReadOnlyTargetRules Target, string dll)
    {
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            return dll + ".dll";
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            return "lib" + dll + ".dylib";
        }
        else
        {
            return "lib" + dll + ".so";
        }
    }

}
