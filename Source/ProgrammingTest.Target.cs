// Programming Test: underDOGS Studio

using UnrealBuildTool;
using System.Collections.Generic;

public class ProgrammingTestTarget : TargetRules
{
	public ProgrammingTestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "ProgrammingTest" } );
	}
}
