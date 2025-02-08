// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleActorBase.h"

// Sets default values
APuzzleActorBase::APuzzleActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzleEntityMesh"));
	RootComponent = PuzzleMesh;

}

void APuzzleActorBase::SetupNodeConnections()
{
}

void APuzzleActorBase::DrawDebugConnection()
{
}

