// Programming Test: underDOGS Studio


#include "PuzzleComponents/PuzzleNodeConnectionComponent.h"

#include "PuzzleManagers/PuzzleNodes.h"

// Sets default values for this component's properties
UPuzzleNodeConnectionComponent::UPuzzleNodeConnectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPuzzleNodeConnectionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPuzzleNodeConnectionComponent::SetupNodeConnection(TArray<APuzzleNodes*> SpawnedNodes, FVector CenterLocationNode,int MatrixSize)
{
	//Traversing diagonals and connecting them
	//1st cross top to bottom
	APuzzleNodes* PreviousActor = nullptr;
	TSet<APuzzleNodes*> SpawnedNodeSet;
	for (int i = 0, j = 0; i < MatrixSize; i++,j += (MatrixSize + 1))
	{
		APuzzleNodes* CurrentActor = SpawnedNodes[j];
		if (PreviousActor == nullptr)
		{
			PreviousActor = CurrentActor;
		}
		else if (PreviousActor != nullptr && (PreviousActor->GetActorLocation() - CenterLocationNode).Length() <= 1.0f)
		{
			PreviousActor = CurrentActor;
			continue;
		}
		else
		{
			if (!SpawnedNodeSet.Contains(PreviousActor))
			{
				SpawnedNodeSet.Add(PreviousActor);
				DebuggingNodes.Add(PreviousActor);
			}
			PreviousActor->ConnectedNodes.AddUnique(CurrentActor);
			PreviousActor = CurrentActor;
		}
	}
	//2nd cross top to bottom
	PreviousActor = nullptr;
	for (int i = 0, j = MatrixSize - 1; i < MatrixSize; i++,j += (MatrixSize - 1))
	{
		APuzzleNodes* CurrentActor = SpawnedNodes[j];
		if (PreviousActor == nullptr)
		{
			PreviousActor = CurrentActor;
		}
		else if (PreviousActor != nullptr && (PreviousActor->GetActorLocation() - CenterLocationNode).Length() <= 1.0f)
		{
			PreviousActor = CurrentActor;
			continue;
		}
		else
		{
			if (!SpawnedNodeSet.Contains(PreviousActor))
			{
				SpawnedNodeSet.Add(PreviousActor);
				DebuggingNodes.Add(PreviousActor);
			}
			PreviousActor->ConnectedNodes.AddUnique(CurrentActor);
			PreviousActor = CurrentActor;
		}
	}
	//3rd cross bottom to top
	PreviousActor = nullptr;
	for (int i = 0, j = (SpawnedNodes.Num() - 1) - (MatrixSize - 1); i < MatrixSize; i++,j -= (MatrixSize - 1))
	{
		APuzzleNodes* CurrentActor = SpawnedNodes[j];
		if (PreviousActor == nullptr)
		{
			PreviousActor = CurrentActor;
		}
		else if (PreviousActor != nullptr && (PreviousActor->GetActorLocation() - CenterLocationNode).Length() <= 1.0f)
		{
			PreviousActor = CurrentActor;
			continue;
		}
		else
		{
			if (!SpawnedNodeSet.Contains(PreviousActor))
			{
				SpawnedNodeSet.Add(PreviousActor);
				DebuggingNodes.Add(PreviousActor);
			}
			PreviousActor->ConnectedNodes.AddUnique(CurrentActor);
			PreviousActor = CurrentActor;
		}
	}
	//4th cross bottom to top
	PreviousActor = nullptr;
	for (int i = 0, j = (SpawnedNodes.Num() - 1); i < MatrixSize; i++,j -= (MatrixSize + 1))
	{
		APuzzleNodes* CurrentActor = SpawnedNodes[j];
		if (PreviousActor == nullptr)
		{
			PreviousActor = CurrentActor;
		}
		else if (PreviousActor != nullptr && (PreviousActor->GetActorLocation() - CenterLocationNode).Length() <= 1.0f)
		{
			PreviousActor = CurrentActor;
			continue;
		}
		else
		{
			if (!SpawnedNodeSet.Contains(PreviousActor))
			{
				SpawnedNodeSet.Add(PreviousActor);
				DebuggingNodes.Add(PreviousActor);
			}
			PreviousActor->ConnectedNodes.AddUnique(CurrentActor);
			PreviousActor = CurrentActor;
		}
	}
	/*
	// Sorting nodes by Y coordinate to group rows
	SpawnedNodes.Sort([](const APuzzleNodes& A, const APuzzleNodes& B) {
		return A.GetActorLocation().Y < B.GetActorLocation().Y;
	});

	// Grouping nodes by rows based on Y coordinate
	TMap<float, TArray<APuzzleNodes*>> RowGroups;
	for (APuzzleNodes* Node : SpawnedNodes)
	{
		float YCoord = Node->GetActorLocation().Y;
		if (!RowGroups.Contains(YCoord))
		{
			RowGroups.Add(YCoord, TArray<APuzzleNodes*>());
		}
		RowGroups[YCoord].Add(Node);
	}

     //Sorting nodes within each row based on x coordinate
	for (auto& Row : RowGroups)
	{
		Row.Value.Sort([](const APuzzleNodes& A, const APuzzleNodes& B) {
			return A.GetActorLocation().X < B.GetActorLocation().X;
		});

		// Connecting adjacent nodes in row
		for (int32 i = 0; i < Row.Value.Num() - 1; i++)
		{
			Row.Value[i]->ConnectedNodes.AddUnique(Row.Value[i + 1]);
			Row.Value[i + 1]->ConnectedNodes.AddUnique(Row.Value[i]);
		}
	}

	// Sorting nodes by X coordinate
	SpawnedNodes.Sort([](const APuzzleNodes& A, const APuzzleNodes& B) {
		return A.GetActorLocation().X < B.GetActorLocation().X;
	});

	// Grouping by columns
	TMap<float, TArray<APuzzleNodes*>> ColumnGroups;
	for (APuzzleNodes* Node : SpawnedNodes)
	{
		float ZCoord = Node->GetActorLocation().X;
		if (!ColumnGroups.Contains(ZCoord))
		{
			ColumnGroups.Add(ZCoord, TArray<APuzzleNodes*>());
		}
		ColumnGroups[ZCoord].Add(Node);
	} 

	// Sorting nodes within each column based on y coordinate
	for (auto& Column : ColumnGroups)
	{
		Column.Value.Sort([](const APuzzleNodes& A, const APuzzleNodes& B) {
			return A.GetActorLocation().Y < B.GetActorLocation().Y;
		});

		for (int32 i = 0; i < Column.Value.Num() - 1; i++)
		{
			Column.Value[i]->ConnectedNodes.AddUnique(Column.Value[i + 1]);
			Column.Value[i + 1]->ConnectedNodes.AddUnique(Column.Value[i]);
		}
	}
	// Now adding only the specific diagonal connections to form the X pattern
	//Find center node
	APuzzleNodes* CenterNode = nullptr;
	FVector CenterLocation = CenterLocationNode;
	float ClosestToCenterDist = MAX_FLT;

	for (APuzzleNodes* Node : SpawnedNodes)
	{
		float DistToCenter = FVector::Distance(Node->GetActorLocation(), CenterLocation);
		if (DistToCenter < ClosestToCenterDist)
		{
			ClosestToCenterDist = DistToCenter;
			CenterNode = Node;
		}
	}

	if (CenterNode)
	{
		// Finding and connecting the four corner nodes that form the X
		for (APuzzleNodes* PotentialCornerNode : SpawnedNodes)
		{
			FVector DirectionToCorner = PotentialCornerNode->GetActorLocation() - CenterNode->GetActorLocation();
			DirectionToCorner.Normalize();

			// Checking if this node forms one of the diagonal connections
			bool bIsDiagonal = FMath::IsNearlyEqual(FMath::Abs(DirectionToCorner.X), 0.707f, 0.1f) &&
						  FMath::IsNearlyEqual(FMath::Abs(DirectionToCorner.Y), 0.707f, 0.1f);

			if (bIsDiagonal)
			{
				// Connecting this corner node to the center
				CenterNode->ConnectedNodes.AddUnique(PotentialCornerNode);
				PotentialCornerNode->ConnectedNodes.AddUnique(CenterNode);
				DebuggingNodes.Add(PotentialCornerNode);
			}
		}
	}*/
	

	//checking Connection
	DrawDebugConnection(DebuggingNodes);
}


void UPuzzleNodeConnectionComponent::DrawDebugConnection(TArray<APuzzleNodes*> SpawnedNodes)
{
	for (int i = 0;i < SpawnedNodes.Num();i++)
	{
		if (SpawnedNodes[i])
		{
			FVector StartLoc = SpawnedNodes[i]->GetActorLocation();
			
			for (AActor* ConnectedNode : SpawnedNodes[i]->ConnectedNodes)
			{
				if (ConnectedNode)
				{
					FVector EndLoc = ConnectedNode->GetActorLocation();
					
					DrawDebugLine(
						GetWorld(),
						StartLoc,
						EndLoc,
						FColor::Red, 
						true,         
						-1.f,       
						0,              
						2.f             
					);
				}
			}
			DrawDebugSphere(
				GetWorld(),
				StartLoc,
				10.f,      
				12,
				FColor::Green,  
				true,        
				-1.f
				);
		}
	}
}

