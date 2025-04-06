// Programming Test: underDOGS Studio


#include "PuzzlePieces/PuzzleCrescentPiece.h"

#include "CollisionDebugDrawingPublic.h"
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
	CapsuleComponent->SetCapsuleSize(0.1f,0.1f);
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
}

void APuzzleCrescentPiece::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CapsuleComponent->SetCapsuleSize(38.f, 38.f);
}

void APuzzleCrescentPiece::UnPossessed()
{
	Super::UnPossessed();
	CapsuleComponent->SetCapsuleSize(0.1f, 0.1f);
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
			MovementComponent->StopActiveMovement();
		}

		if ((GetActorLocation() - HomeLocation).Length() <= 6.0f)
		{
			bIsHome = true;
			MovementComponent->StopActiveMovement();
			OnIsHome.Execute();
			
		} 
	}
}

void APuzzleCrescentPiece::PuzzleMovement(const struct FInputActionValue& InputActionValue)
{
	if (bIsHome) return;
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	if (InputAxisVector.IsNearlyZero()) return;
  
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	CapsuleComponent->GetOverlappingActors(OverlappingActors);
	// Find the best target node based on the input direction
	float BestDotProduct = -1.0f;
	const FVector InputDirection = (ForwardDirection * InputAxisVector.Y + RightDirection * InputAxisVector.X).GetSafeNormal();
	TargetActor = nullptr;
	bIsTargetNode = false;
	IgnoreDirections.Empty();
	TArray<AActor*> AdditionalActors;
	for (AActor* Actor : OverlappingActors)
	{
		APuzzleNodes* Node = Cast<APuzzleNodes>(Actor);
		if (Node)
		{
			if (Node->ConnectedNodes.Num() > 0)
			{
				AdditionalActors.Append(Node->ConnectedNodes);
			}
		}
		if (const APuzzleCrescentPiece* CrescentPiece = Cast<APuzzleCrescentPiece>(Actor))
		{
			const FVector Direction = (Actor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			IgnoreDirections.Add(Direction);
		}
	}
	OverlappingActors.Append(AdditionalActors);
	for (AActor* OverlappedActor: OverlappingActors)
	{
		if ((GetActorLocation() - OverlappedActor->GetActorLocation()).Length() <= 2.0) continue;
		
		FVector PathDirection = (OverlappedActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		float DotProduct = FVector::DotProduct(InputDirection, PathDirection);
		if (DotProduct < 0.8f) continue;
		bShouldIgnore = false;
		for (FVector DirectionToAvoid : IgnoreDirections)
		{
			float AvoidDotProduct = FVector::DotProduct(DirectionToAvoid, InputDirection);
			if (AvoidDotProduct > 0.9f)
			{
				bShouldIgnore = true;
				break;
			}
		}
		if (bShouldIgnore) continue;
		if (DotProduct > BestDotProduct)
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



