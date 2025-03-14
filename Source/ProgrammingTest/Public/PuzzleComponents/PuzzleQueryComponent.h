// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleQueryComponent.generated.h"


class APuzzleBoard;
class APuzzleNodes;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGRAMMINGTEST_API UPuzzleQueryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleQueryComponent();

	// The currently selected node
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	TObjectPtr<APuzzleNodes> CurrentNode;

	// Reference to the puzzle board
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<APuzzleBoard> PuzzleBoard;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TObjectPtr<APuzzleBoard> BoardInstance;
		
};
