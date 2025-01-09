// Programming Test: underDOGS Studio


#include "PuzzleCharacterBase.h"

// Sets default values
APuzzleCharacterBase::APuzzleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzleCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

