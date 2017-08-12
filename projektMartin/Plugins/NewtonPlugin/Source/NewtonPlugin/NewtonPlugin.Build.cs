// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class NewtonPlugin : ModuleRules
	{
		private string ModulePath
		{
			get { return ModuleDirectory; }
		}
		
		public NewtonPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"NewtonPlugin/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core", 
					"CoreUObject", 
					"Engine", 
					"InputCore", 
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
			
			PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "..", "..", "Binaries", "Win64", "sharedspice.lib"));
			//PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "..", "..", "ThirdParty", "Ngspice", "sharedspice.lib"));
		}
	}
}
