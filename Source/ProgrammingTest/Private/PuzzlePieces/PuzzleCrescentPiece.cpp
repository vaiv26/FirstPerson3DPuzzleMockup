// Programming Test: underDOGS Studio


#include "PuzzlePieces/PuzzleCrescentPiece.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PuzzleComponents/PuzzleQueryComponent.h"
#include "PuzzleManagers/PuzzleNodes.h"

// Sets default values
APuzzleCrescentPiece::APuzzleCrescentPiece()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CapsuleComponent->SetCollisionProfileName(TEXT("Custom"));
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	CrescentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrescentMeshComponent"));
	CrescentMesh->SetupAttachment(CapsuleComponent);
	CrescentMesh->SetGenerateOverlapEvents(false); 
	CrescentMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	QueryActorComponent = CreateDefaultSubobject<UPuzzleQueryComponent>(TEXT("PuzzleQueries"));
	AddOwnedComponent(QueryActorComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 50.0f;
	MovementComponent->Acceleration = 50.f;
	MovementComponent->Deceleration = 200.f;
}

void APuzzleCrescentPiece::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,&APuzzleCrescentPiece::OnComponentOverlap);
}

void APuzzleCrescentPiece::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherCoponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APuzzleCrescentPiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APuzzleCrescentPiece::PuzzleMovement);
}

void APuzzleCrescentPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement();
}

void APuzzleCrescentPiece::UpdateMovement()
{
	if (bIsTargetNode && TargetActor != nullptr && !bIsHome)
	{
		const FVector EndPos = TargetActor->GetActorLocation();
		const FVector MoveDirection = (EndPos - GetActorLocation()).GetSafeNormal();
    
		MovementComponent->AddInputVector(MoveDirection); // Smooth movement

		if ((GetActorLocation() - EndPos).Length() <= MovementThreshold)
		{
			bIsTargetNode = false;
			//QueryActorComponent->CurrentNode->bIsOccupied= false;
			//QueryActorComponent->CurrentNode = TargetNode;
			//QueryActorComponent->CurrentNode->bIsOccupied = true;
			MovementComponent->StopActiveMovement();
		}

		if ((GetActorLocation() - HomeLocation).Length() <= 2.0f)
		{
			bIsHome = true;
			OnIsHome.Execute();
		} 
	}
}

void APuzzleCrescentPiece::PuzzleMovement(const struct FInputActionValue& InputActionValue)
{
	if (!QueryActorComponent->CurrentNode || bIsHome) return;
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	if (InputAxisVector.IsNearlyZero()) return;
  
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	CapsuleComponent->GetOverlappingActors(OverlappingActors);
	// Find the best target node based on the input direction
	float BestDotProduct = -1.0f;
	const FVector InputDirection = (ForwardDirection * InputAxisVector.Y + RightDirection * InputAxisVector.X).GetSafeNormal();
	//TargetNode = nullptr;
	TargetActor = nullptr;
	bIsTargetNode = false;
	IgnoreLocations.Empty();
	/*
	for (APuzzleNodes* ConnectedNode : QueryActorComponent->CurrentNode->ConnectedNodes)
	{
		if (ConnectedNode->bIsOccupied) continue;
		
		FVector PathDirection = (ConnectedNode->GetActorLocation() - QueryActorComponent->CurrentNode->GetActorLocation()).GetSafeNormal();
		float DotProduct = FVector::DotProduct(InputDirection, PathDirection);

		if (DotProduct > 0.8f && DotProduct > BestDotProduct)
		{
			BestDotProduct = DotProduct;
			TargetNode = ConnectedNode;
		}
	}
	if (TargetNode != nullptr)
	{
		bIsTargetNode = true;
		UE_LOG(LogTemp,Display, TEXT("The name of the target Node: [%s]"),*TargetNode.GetName());
	}
	*/
	TArray<AActor*> AdditionalActors;
	for (AActor* Actor : OverlappingActors)
	{
		APuzzleNodes* Node = Cast<APuzzleNodes>(Actor);
		if (Node && Node->ConnectedNodes.Num() > 0)
		{
			AdditionalActors.Append(Node->ConnectedNodes);
		}
		if (const APuzzleCrescentPiece* CrescentPiece = Cast<APuzzleCrescentPiece>(Actor))
		{
			IgnoreLocations.Add(Actor->GetActorLocation());
		}
	}
	OverlappingActors.Append(AdditionalActors);
	for (AActor* OverlappedActor: OverlappingActors)
	{
		if ((GetActorLocation() - OverlappedActor->GetActorLocation()).Length() <= 2.0 ||
			IgnoreLocations.Contains(OverlappedActor->GetActorLocation())) continue;
		
		FVector PathDirection = (OverlappedActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		float DotProduct = FVector::DotProduct(InputDirection, PathDirection);
		if (DotProduct > 0.8f && DotProduct > BestDotProduct)
		{
			BestDotProduct = DotProduct;
			TargetActor = OverlappedActor;
		}
	}
	if (TargetActor != nullptr)
	{
		bIsTargetNode = true;
	}

}



