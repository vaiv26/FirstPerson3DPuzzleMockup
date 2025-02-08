// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleActorTeleport.h"

#include "Components/BoxComponent.h"

// Sets default values
APuzzleActorTeleport::APuzzleActorTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));
	RootComponent = BoxColliderComponent;
	BoxColliderComponent->SetGenerateOverlapEvents(true);
	BoxColliderComponent->SetCollisionProfileName(TEXT("Trigger"));
	
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void APuzzleActorTeleport::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APuzzleActorTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

