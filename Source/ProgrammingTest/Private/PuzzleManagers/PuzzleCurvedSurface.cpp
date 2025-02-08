// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleCurvedSurface.h"

#include "Components/SplineComponent.h"

APuzzleCurvedSurface::APuzzleCurvedSurface()
{
	GridRows = 0;
}

void APuzzleCurvedSurface::SetupNodeConnections()
{
	for (int i = 0;i < SplinePath.Num();i++)
	{
		int PointsOnSpline = SplinePath[i]->GetNumberOfSplinePoints();
		for (int j = 0;j < PointsOnSpline;j++)
		{
			int Row = j % PointsOnSpline;
			FPuzzleCurvedNodeData CurvedNewNode;
			CurvedNewNode.NodeLocation = SplinePath[j]->GetSplinePointAt(j,ESplineCoordinateSpace::World).Position;
			CurvedNewNode.NodeTangent = SplinePath[j]->GetTangentAtSplinePoint(j,ESplineCoordinateSpace::World);
			
			if (Row < PointsOnSpline - 1)
				CurvedNewNode.ConnectedNodesLocation.Add(SplinePath[j]->GetSplinePointAt(j + 1,ESplineCoordinateSpace::World).Position);
			if (Row > 0)
				CurvedNewNode.ConnectedNodesLocation.Add(SplinePath[j]->GetSplinePointAt(j - 1,ESplineCoordinateSpace::World).Position);
			
			CurvedNodeData.Add(CurvedNewNode);
		}
	}
	DrawDebugConnection();
}

void APuzzleCurvedSurface::DrawDebugConnection()
{
	for (int32 i = 0; i < CurvedNodeData.Num(); ++i)
	{
		// Draw node points
		DrawDebugSphere(
			GetWorld(),
			CurvedNodeData[i].NodeLocation,
			10.0f,  // Radius
			12,     // Segments
			FColor::Red,
			false,  // Persistent
			-1.f
		);

		// Draw connections
		for (FVector ConnectedNodeLocation : CurvedNodeData[i].ConnectedNodesLocation)
		{
			// Draw line for each connection
			DrawDebugLine(
				GetWorld(),
				CurvedNodeData[i].NodeLocation,
				ConnectedNodeLocation,
				FColor::Green,
				false,   // Persistent
				-1.f,
				0,      // DepthPriority
				2.0f    // Thickness
			);

			// Optionally draw tangent
			DrawDebugDirectionalArrow(
				GetWorld(),
				CurvedNodeData[i].NodeLocation,
				CurvedNodeData[i].NodeLocation + CurvedNodeData[i].NodeTangent * 50.0f,  // Scale tangent for visibility
				20.0f,  // Arrow size
				FColor::Blue,
				false,
				-1.f
			);
		}
	}
}

void APuzzleCurvedSurface::BeginPlay()
{
	Super::BeginPlay();
	SetupNodeConnections();
}
