// Programming Test: underDOGS Studio


#include "PuzzleComponents/PuzzleQueryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "PuzzleManagers/PuzzleBoard.h"
#include "PuzzleManagers/PuzzleNodes.h"

// Sets default values for this component's properties
UPuzzleQueryComponent::UPuzzleQueryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPuzzleQueryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (PuzzleBoard)
	{
		BoardInstance = CastChecked<APuzzleBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), PuzzleBoard));
		CurrentNode = BoardInstance->GetClosestNode(GetOwner()->GetActorLocation());
		if (CurrentNode)
		{
			CurrentNode->bIsOccupied = true;
		}
	}
}

