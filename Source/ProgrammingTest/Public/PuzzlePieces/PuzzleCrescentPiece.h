// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PuzzleCrescentPiece.generated.h"

class UPuzzleQueryComponent;

UCLASS()
class PROGRAMMINGTEST_API APuzzleCrescentPiece : public APawn
{
	GENERATED_BODY()

public:
	APuzzleCrescentPiece();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CrescentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPuzzleQueryComponent* QueryActorComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector HomeLocation;

private:
	UPROPERTY()
	bool bIsHome = false;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector CurrentVelocity;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool IsMovingToNode;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector TargetLocation;
	
	void UpdateMovement(float DeltaTime);

	UPROPERTY(EditAnywhere,Category="Movement")
	FVector PendingMovementInput;

};
