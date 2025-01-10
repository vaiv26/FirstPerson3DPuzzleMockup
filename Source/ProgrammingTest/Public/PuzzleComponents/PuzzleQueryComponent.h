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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Reference to the puzzle board
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<APuzzleBoard> PuzzleBoard;

	TObjectPtr<APuzzleBoard> BoardInstance;

	// The currently selected node
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	TObjectPtr<APuzzleNodes> CurrentNode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Puzzle")
	FVector CenterLocation;

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void FoundHome();
		
};
