// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleNodes.generated.h"

UCLASS()
class PROGRAMMINGTEST_API APuzzleNodes : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleNodes();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TArray<APuzzleNodes*> ConnectedNodes;
	
	UFUNCTION(BlueprintCallable, Category = "Node")
	bool IsConnectedTo(APuzzleNodes* OtherNode) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node")
	bool bIsOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node")
	bool bIsCenterNode;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
