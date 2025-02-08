// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleBox.h"

APuzzleBox::APuzzleBox()
{
	GridColumns = 0;
	GridRows = 0;
}

void APuzzleBox::SetupNodeConnections()
{
	for(int i = 0;i < NodeTargetPoints.Num();i++)
	{
		
		FPuzzleNodeData NewNode;
		if(NodeTargetPoints[i] != nullptr)
		{
			NewNode.NodeLocation  = NodeTargetPoints[i]->GetActorLocation();
		}
		int Row = i / GridColumns;
		int Col = i % GridColumns;
		
		//Connect Horizontal nodes
		if(Col < GridColumns - 1)
			NewNode.ConnectedNodesLocation.Add(NodeTargetPoints[i + 1]->GetActorLocation());
		if (Col > 0)
			NewNode.ConnectedNodesLocation.Add(NodeTargetPoints[i - 1]->GetActorLocation());

		//Connect Vertical nodes
		if (Row < GridRows - 1)
			NewNode.ConnectedNodesLocation.Add(NodeTargetPoints[i + GridColumns]->GetActorLocation());
		if (Row > 0)
			NewNode.ConnectedNodesLocation.Add(NodeTargetPoints[i -  GridColumns]->GetActorLocation());

		Nodes.Add(NewNode);
	}
	if (GridColumns == GridRows)
	{
		for (int i = 0;i < NodeTargetPoints.Num();i++)
		{
			int Row = i / GridColumns;
			int Col = i % GridColumns;
		
			// Connect diagonal to center
			int32 CenterRow = GridRows / 2;
			int32 CenterCol = GridColumns / 2;
			int32 CenterIndex = CenterRow * GridColumns + CenterCol;

			// Check if current node is a corner
			bool IsCorner = (Row == 0 || Row == GridRows - 1) && 
						   (Col == 0 || Col == GridColumns - 1);

			if (IsCorner)
			{
				Nodes[i].ConnectedNodesLocation.Add(NodeTargetPoints[CenterIndex]->GetActorLocation());
				Nodes[CenterIndex].ConnectedNodesLocation.Add(NodeTargetPoints[i]->GetActorLocation());
			}
		}
	}

	DrawDebugConnection();
}

void APuzzleBox::DrawDebugConnection()
{
	for (FPuzzleNodeData Node : Nodes)
	{
		FVector StartLoc = Node.NodeLocation;
		
		for (FVector ConnectedNodeLocation : Node.ConnectedNodesLocation)
		{
			FVector EndLoc = ConnectedNodeLocation;
			
			DrawDebugLine(
				GetWorld(),
				StartLoc,
				EndLoc,
				FColor::Green, 
				true,         
				-1.f,       
				0,              
				2.f             
			);
			
			DrawDebugSphere(
				GetWorld(),
				StartLoc,
				10.f,      
				12,         
				FColor::Red,  
				true,        
				-1.f          
			);
		}
	}
}

void APuzzleBox::BeginPlay()
{
	Super::BeginPlay();

	SetupNodeConnections();
}
