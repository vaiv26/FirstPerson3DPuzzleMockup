// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PuzzleCrescentPiece.generated.h"

class APuzzleNodes;
class UInputAction;
class UPuzzleQueryComponent;
class UFloatingPawnMovement;

DECLARE_DELEGATE(FISHomeDelegate);

UCLASS()
class PROGRAMMINGTEST_API APuzzleCrescentPiece : public APawn
{
	GENERATED_BODY()

public:
	APuzzleCrescentPiece();

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:	

	virtual void Tick(float DeltaTime) override;

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

	FISHomeDelegate OnIsHome;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
	float MovementThreshold = 2.f;

private:
	bool bIsHome = false;
	bool bIsTargetNode = false;
	bool bShouldIgnore = false;
	TObjectPtr<APuzzleNodes> TargetNode = nullptr;
	TObjectPtr<AActor> TargetActor  = nullptr;
	TArray<AActor*> OverlappingActors;
	TArray<FVector> IgnoreDirections;
	
	UPROPERTY(EditAnywhere,Category = "Movement")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void PuzzleMovement(const struct FInputActionValue& InputActionValue);
	void UpdateMovement();

};
