// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleSplineActor.h"

#include "Components/SplineComponent.h"

// Sets default values
APuzzleSplineActor::APuzzleSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("PuzzleSplineComponent");
}

// Called when the game starts or when spawned
void APuzzleSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

