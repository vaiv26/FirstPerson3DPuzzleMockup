// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleNodes.h"

APuzzleNodes::APuzzleNodes()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}

// Called when the game starts or when spawned
void APuzzleNodes::BeginPlay()
{
	Super::BeginPlay();
	
}
