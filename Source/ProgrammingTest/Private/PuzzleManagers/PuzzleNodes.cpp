// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleNodes.h"

APuzzleNodes::APuzzleNodes()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}

bool APuzzleNodes::IsConnectedTo(APuzzleNodes* OtherNode) const
{
	return ConnectedNodes.Contains(OtherNode);
}

// Called when the game starts or when spawned
void APuzzleNodes::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleNodes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

