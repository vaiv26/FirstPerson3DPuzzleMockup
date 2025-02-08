// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "PuzzleManagers/PuzzleActorBase.h"
#include "PuzzleBox.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGTEST_API APuzzleBox : public APuzzleActorBase
{
	GENERATED_BODY()

public:
	APuzzleBox();

protected:
	virtual void SetupNodeConnections() override;
	virtual void DrawDebugConnection() override;

	virtual void BeginPlay() override;

private:
	TArray<FPuzzleNodeData> Nodes;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 GridRows;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 GridColumns;


	
};
