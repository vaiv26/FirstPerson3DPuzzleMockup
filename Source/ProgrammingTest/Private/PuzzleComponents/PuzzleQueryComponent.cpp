// Programming Test: underDOGS Studio


#include "PuzzleComponents/PuzzleQueryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "PuzzleManagers/PuzzleBoard.h"
#include "PuzzleManagers/PuzzleNodes.h"

// Sets default values for this component's properties
UPuzzleQueryComponent::UPuzzleQueryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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
			CenterLocation = BoardInstance->CenterLocationNode;
		}
	}
}




// Called every frame
void UPuzzleQueryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPuzzleQueryComponent::FoundHome()
{
	BoardInstance->CompletionEvent();
}

