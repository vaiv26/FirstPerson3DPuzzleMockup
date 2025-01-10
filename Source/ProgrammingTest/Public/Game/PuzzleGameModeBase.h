// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGTEST_API APuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PuzzleGameModeBase")
	void PuzzleCompletionEvent();
	
};
