// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBoard.generated.h"

class UPuzzleNodeConnectionComponent;
class APuzzleNodes;

DECLARE_DELEGATE(FOnPuzzleCompleted);

UCLASS()
class PROGRAMMINGTEST_API APuzzleBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleBoard();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Nodes")
	TArray<APuzzleNodes*> SpawnedNodes;

	UPROPERTY(EditAnywhere,Category="Pawns")
	int32 PawnFoundHome;

	// Function to spawn nodes
	UFUNCTION(Category = "Nodes")
	void SpawnNodes();
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Nodes")
	int32 BoardMatrixSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	AActor* CenterLocationNode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PuzzleBoardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPuzzleNodeConnectionComponent* ConnectionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TArray<AActor*> NodeTargetPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TSubclassOf<APuzzleNodes> NodeClass;
	
	TObjectPtr<APuzzleNodes> GetClosestNode(FVector ActorLocation);

	UFUNCTION(BlueprintCallable,Category = "Nodes")
	void CompletionEvent();

	FOnPuzzleCompleted OnPuzzleCompleted;
};
