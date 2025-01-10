// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleBoard.generated.h"

class APuzzleNodes;

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

	//Function to Set ConnectedNodes Variable 
	UFUNCTION(Category = "Nodes")
	void SetupNodeConnectionsByPattern();

	UFUNCTION(Category = "Nodes")
	void DrawDebugConnection();
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	FVector CenterLocationNode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PuzzleBoardMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TArray<AActor*> NodeTargetPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TSubclassOf<APuzzleNodes> NodeClass;
	
	TObjectPtr<APuzzleNodes> GetClosestNode(FVector ActorLocation);

	UFUNCTION(BlueprintCallable,Category = "Nodes")
	void CompletionEvent();
};
