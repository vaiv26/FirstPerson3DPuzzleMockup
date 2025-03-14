// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleBoard.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleComponents/PuzzleNodeConnectionComponent.h"
#include "PuzzleManagers/PuzzleNodes.h"
#include "PuzzlePieces/PuzzleCrescentPiece.h"

APuzzleBoard::APuzzleBoard()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PuzzleBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleBoardMesh"));
	RootComponent = PuzzleBoardMesh;

	ConnectionComponent = CreateDefaultSubobject<UPuzzleNodeConnectionComponent>(TEXT("NodeConnectionComponent"));
	AddOwnedComponent(ConnectionComponent);
	
	NodeClass = APuzzleNodes::StaticClass();
}

void APuzzleBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnNodes();

	TArray<AActor*> PieceActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleCrescentPiece::StaticClass(), PieceActors);
	for (AActor* Actor : PieceActors)
	{
		if (APuzzleCrescentPiece* Piece = Cast<APuzzleCrescentPiece>(Actor))
		{
			// Bind to the delegate
			Piece->OnIsHome.BindUObject(this, &APuzzleBoard::CompletionEvent);
		}
	}
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
	//SetupNodeConnectionsByPattern();
	ConnectionComponent->SetupNodeConnection(SpawnedNodes, CenterLocationNode);
}

void APuzzleBoard::CompletionEvent()
{
	PawnFoundHome += 1;
	if (PawnFoundHome >= 4)
	{
		OnPuzzleCompleted.Execute();
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


