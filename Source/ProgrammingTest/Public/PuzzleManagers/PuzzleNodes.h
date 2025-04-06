// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleNodes.generated.h"

class USphereComponent;

UCLASS()
class PROGRAMMINGTEST_API APuzzleNodes : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleNodes();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TArray<AActor*> ConnectedNodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	USphereComponent* CollisionComponent;
	
	bool bCanMove = true;
	
protected:
	virtual void BeginPlay() override;

};
