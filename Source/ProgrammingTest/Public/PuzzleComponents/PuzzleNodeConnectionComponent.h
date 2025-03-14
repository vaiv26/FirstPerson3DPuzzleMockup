// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleNodeConnectionComponent.generated.h"


class APuzzleNodes;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGTEST_API UPuzzleNodeConnectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleNodeConnectionComponent();

	UFUNCTION()
	void SetupNodeConnection(TArray<APuzzleNodes*> SpawnedNodes, FVector CenterLocationNode);

	UFUNCTION(Category = "Nodes")
	void DrawDebugConnection(TArray<APuzzleNodes*> SpawnedNodes);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
