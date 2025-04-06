// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzlePlayerController.generated.h"

class APuzzleCameraActor;
class APuzzleFirstPerson;
class APuzzleCrescentPiece;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class PROGRAMMINGTEST_API APuzzlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APuzzlePlayerController();

	UFUNCTION(BlueprintCallable, Category = "Switch")
	void SwitchAndPossess();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TSubclassOf<APuzzleCameraActor> FixedCameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Pawns")
	TObjectPtr<APawn> FirstPerson;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pawns")
	TArray<FVector> PawnLocations;

	UFUNCTION(BlueprintCallable, Category = "Home")
	void InvokeCompletionEvent();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Puzzle")
	bool bPuzzleCompleted = false;

private:
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PuzzleContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;
	
	TArray<APuzzleCrescentPiece*> FoundPawns;

	UPROPERTY(EditAnywhere, Category = "Pawns")
	int32 CurrentPawn ;

	UPROPERTY(EditAnywhere, Category = "Pawns")
	int32 NextPawn;

	void Move(const struct FInputActionValue& InputActionValue);
	
	void SwitchToNextPuzzlePiece();
	
	bool bCanPerformAction;

	// Cooldown Time
	float CooldownTime;

	// Timer Handle
	FTimerHandle CooldownTimerHandle;
	
	void ResetCooldown();

	void DrawPawnHighlight(APawn* TargetPawn, FColor Color = FColor::Red);
	
};
