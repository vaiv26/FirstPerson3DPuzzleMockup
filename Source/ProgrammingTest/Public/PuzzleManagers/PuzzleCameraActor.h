// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SequenceInterface.h"
#include "PuzzleCameraActor.generated.h"

class UCameraComponent;

UCLASS()
class PROGRAMMINGTEST_API APuzzleCameraActor : public AActor, public ISequenceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleCameraActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "SequenceCamera")
	UCameraComponent* CineCamera;

};
