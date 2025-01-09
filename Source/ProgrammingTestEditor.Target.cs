// Programming Test: underDOGS Studio

using UnrealBuildTool;
using System.Collections.Generic;

public class ProgrammingTestEditorTarget : TargetRules
{
	public ProgrammingTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "ProgrammingTest" } );
	}
}
