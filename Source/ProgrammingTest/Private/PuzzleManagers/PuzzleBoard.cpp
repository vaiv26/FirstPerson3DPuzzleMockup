// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleBoard.h"

#include "Game/PuzzleGameModeBase.h"
#include "PuzzleManagers/PuzzleNodes.h"

APuzzleBoard::APuzzleBoard()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PuzzleBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleBoardMesh"));
	RootComponent = PuzzleBoardMesh;
	
	NodeClass = APuzzleNodes::StaticClass();
}

void APuzzleBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnNodes();
}

// Called every frame
void APuzzleBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleBoard::SpawnNodes()
{
	if (!NodeClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("NodeClass is not set!"));
		return;
	}

	if (NodeTargetPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target Points specified for nodes!"));
		return;
	}

	if (!NodeClass) return;

	for (const AActor* TargetPoint : NodeTargetPoints)
	{
		if (!TargetPoint) continue;
		
		FVector WorldPosition = TargetPoint->GetActorLocation();

		// Spawn the node
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		APuzzleNodes* NewNode = GetWorld()->SpawnActor<APuzzleNodes>(NodeClass, WorldPosition, FRotator::ZeroRotator, SpawnParams);

		if (NewNode)
		{
			SpawnedNodes.Add(NewNode);
			if (NewNode->GetActorLocation() == CenterLocationNode)
			{
				NewNode->bIsCenterNode = true;
			}
		}
	}
	//Set Up Node Connections
	SetupNodeConnectionsByPattern();
}

void APuzzleBoard::SetupNodeConnectionsByPattern()
{
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

     //sorting nodes by x and connect adjacent nodes
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

	// Connecting nodes in columns
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
			}
		}
	}

	//checking Connection
	//DrawDebugConnection();
}

void APuzzleBoard::DrawDebugConnection()
{
	for (APuzzleNodes* Node : SpawnedNodes)
	{
		if (Node)
		{
			FVector StartLoc = Node->GetActorLocation();
			
			for (APuzzleNodes* ConnectedNode : Node->ConnectedNodes)
			{
				if (ConnectedNode)
				{
					FVector EndLoc = ConnectedNode->GetActorLocation();
					
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
	}
}

void APuzzleBoard::CompletionEvent()
{
	PawnFoundHome+=1;
	if (PawnFoundHome >= 4)
	{
		//TriggerCompletion of this puzzle
		AGameModeBase* GameModeClass = GetWorld()->GetAuthGameMode();
		if (GameModeClass)
		{
			APuzzleGameModeBase* GameModeBaseClass = Cast<APuzzleGameModeBase>(GameModeClass);
			if (GameModeBaseClass)
			{
				GameModeBaseClass->PuzzleCompletionEvent();
			}
		}
	}
}

TObjectPtr<APuzzleNodes> APuzzleBoard::GetClosestNode(FVector ActorLocation)
{
	float ClosestDistance = MAX_FLT;
	TObjectPtr<APuzzleNodes> ClosestNode = nullptr;
	for (APuzzleNodes* Node : SpawnedNodes)
	{
		float Distance = FVector::Distance(ActorLocation, Node->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestNode = Node;
		}
	}
	return ClosestNode;
}


