// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "PuzzleManagers/PuzzleActorBase.h"
#include "PuzzleCurvedSurface.generated.h"

class USplineComponent;
/**
 * 
 */
UCLASS()
class PROGRAMMINGTEST_API APuzzleCurvedSurface : public APuzzleActorBase
{
	GENERATED_BODY()

public:
	APuzzleCurvedSurface();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleCurvedSurface")
	TArray<USplineComponent*> SplinePath;

protected:
	virtual void SetupNodeConnections() override;
	virtual void DrawDebugConnection() override;

	virtual void BeginPlay() override;

private:
	TArray<FPuzzleCurvedNodeData> CurvedNodeData;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleCurvedSurface")
	int32 GridRows;
	
};
