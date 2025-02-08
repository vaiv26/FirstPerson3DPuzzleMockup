// Programming Test: underDOGS Studio


#include "PuzzlePieces/PuzzleCrescentPiece.h"

#include "Components/CapsuleComponent.h"

#include "PuzzleComponents/PuzzleQueryComponent.h"
#include "PuzzleManagers/PuzzleBoard.h"
#include "PuzzleManagers/PuzzleNodes.h"

// Sets default values
APuzzleCrescentPiece::APuzzleCrescentPiece()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));

	CrescentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrescentMeshComponent"));
	CrescentMesh->SetupAttachment(CapsuleComponent);
	
	CrescentMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	QueryActorComponent = CreateDefaultSubobject<UPuzzleQueryComponent>(TEXT("PuzzleQueries"));
	AddOwnedComponent(QueryActorComponent);
}
void APuzzleCrescentPiece::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzleCrescentPiece::AddMovementInput(const FVector WorldDirection, const float ScaleValue, const bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);

	PendingMovementInput += WorldDirection * ScaleValue;
}

void APuzzleCrescentPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!PendingMovementInput.IsNearlyZero())
	{
		CurrentVelocity = PendingMovementInput * MovementSpeed;
		PendingMovementInput = FVector::ZeroVector;
	}
	else
	{
		CurrentVelocity = FVector::ZeroVector;
	}
    
	UpdateMovement(DeltaTime);

}

void APuzzleCrescentPiece::UpdateMovement(float DeltaTime)
{
	if (!QueryActorComponent->CurrentNode || !QueryActorComponent->PuzzleBoard || bIsHome) return;
	FVector MovementDirection = CurrentVelocity.GetSafeNormal();
	FVector PendingDirection = MovementDirection;

	/*
	if (!MovementDirection.IsZero())
	{
		APuzzleNodes* TargetNode = nullptr;
		APuzzleNodes* PreviousTargetNode = nullptr;
		float BestDotProduct = -1.0f;
		// Find next node based on Input Direction
		for (APuzzleNodes* ConnectedNode : QueryActorComponent->CurrentNode->ConnectedNodes)
		{
			if (ConnectedNode->bIsOccupied) continue;
			
			FVector PathDirection = (ConnectedNode->GetActorLocation() - QueryActorComponent->CurrentNode->GetActorLocation()).GetSafeNormal();
			float DotProduct = FVector::DotProduct(MovementDirection, PathDirection);
            
			// Direction check Threshold
			if (DotProduct > 0.3f && DotProduct > BestDotProduct)
			{
				BestDotProduct = DotProduct;
				TargetNode = ConnectedNode;
			}
		}
		if (TargetNode)
		{
			FVector StartPos = QueryActorComponent->CurrentNode->GetActorLocation();
			FVector EndPos = TargetNode->GetActorLocation();
			
			FVector NewLocation = FMath::VInterpTo(
				GetActorLocation(),
				EndPos,
				DeltaTime,
				5.0f
			);
			
			FVector ProjectedLocation = FMath::ClosestPointOnLine(StartPos, EndPos, NewLocation);
			SetActorLocation(ProjectedLocation);
            
			// Update current node
			if (FVector::Dist(GetActorLocation(), EndPos) < 15.0f)
			{
				SetActorLocation(EndPos); // Snap to exact position
				QueryActorComponent->CurrentNode->bIsOccupied= false;
				QueryActorComponent->CurrentNode = TargetNode;
				QueryActorComponent->CurrentNode->bIsOccupied = true;
			}
		}
		*/
	if (!MovementDirection.IsZero())
	{
	    APuzzleNodes* TargetNode = nullptr;
		APuzzleNodes* PreviousTargetNode = nullptr;
	    float BestDotProduct = -1.0f;

	    // Store pending direction
	    if (!PendingDirection.IsZero())
	    {
	        MovementDirection = PendingDirection;
	    }

	    // Find the next node based on input direction
	    for (APuzzleNodes* ConnectedNode : QueryActorComponent->CurrentNode->ConnectedNodes)
	    {
	        if (ConnectedNode->bIsOccupied) continue;

	        FVector PathDirection = (ConnectedNode->GetActorLocation() - QueryActorComponent->CurrentNode->GetActorLocation()).GetSafeNormal();
	        float DotProduct = FVector::DotProduct(MovementDirection, PathDirection);

	        // Direction check threshold
	        if (DotProduct > 0.3f && DotProduct > BestDotProduct)
	        {
	            BestDotProduct = DotProduct;
	            TargetNode = ConnectedNode;
	        }
	    }

	    // If no valid node is found for the new direction, keep moving in the previous direction
	    if (!TargetNode)
	    {
	        TargetNode = PreviousTargetNode;
	    }
	    else
	    {
	        PreviousTargetNode = TargetNode;
	    }

	    if (TargetNode)
	    {
	        FVector StartPos = QueryActorComponent->CurrentNode->GetActorLocation();
	        FVector EndPos = TargetNode->GetActorLocation();

	        FVector NewLocation = FMath::VInterpTo(
	            GetActorLocation(),
	            EndPos,
	            DeltaTime,
	            2.0f
	        );

	        FVector ProjectedLocation = FMath::ClosestPointOnLine(StartPos, EndPos, NewLocation);
	        SetActorLocation(ProjectedLocation);

	        // Update current node
	        if (FVector::Dist(GetActorLocation(), EndPos) < 15.0f)
	        {
	            SetActorLocation(EndPos); // Snap to exact position
	            QueryActorComponent->CurrentNode->bIsOccupied = false;
	            QueryActorComponent->CurrentNode = TargetNode;
	            QueryActorComponent->CurrentNode->bIsOccupied = true;

	            // If the new direction is valid at this node, apply it
	            for (APuzzleNodes* ConnectedNode : QueryActorComponent->CurrentNode->ConnectedNodes)
	            {
	                FVector PathDir = (ConnectedNode->GetActorLocation() - QueryActorComponent->CurrentNode->GetActorLocation()).GetSafeNormal();
	                float DotProduct = FVector::DotProduct(PendingDirection, PathDir);

	                if (DotProduct > 0.3f)
	                {
	                    MovementDirection = PendingDirection; // Apply new direction
	                    PendingDirection = FVector::ZeroVector;
	                    break;
	                }
	            }
	        }
	    }

		if (FVector::Dist(GetActorLocation(), HomeLocation) < 2.0f)
		{
			//Puzzle Completed by this piece
			bIsHome = true;
			QueryActorComponent->FoundHome();
		}
	}
}

