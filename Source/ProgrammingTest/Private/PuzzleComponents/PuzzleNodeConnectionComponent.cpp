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
	//checking Connection
	//DrawDebugConnection(DebuggingNodes);
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

