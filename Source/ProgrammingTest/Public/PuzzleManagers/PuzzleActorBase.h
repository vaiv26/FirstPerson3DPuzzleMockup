// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleActorBase.generated.h"

USTRUCT(BlueprintType)
struct FPuzzleNodeData
{
	GENERATED_BODY()

	FPuzzleNodeData(){}

	FVector NodeLocation;
	TSet<FVector> ConnectedNodesLocation;
};

USTRUCT(BlueprintType)
struct FPuzzleCurvedNodeData
{
	GENERATED_BODY()
	FPuzzleCurvedNodeData(){}
	
	FVector NodeLocation;
	FVector NodeTangent;
	TArray<FVector> ConnectedNodesLocation;
};

UCLASS()
class PROGRAMMINGTEST_API APuzzleActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActorBase();
	
	virtual void SetupNodeConnections();
	virtual void DrawDebugConnection();

protected:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PuzzleMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TArray<AActor*> NodeTargetPoints;

};
