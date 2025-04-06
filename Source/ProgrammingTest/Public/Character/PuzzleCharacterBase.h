// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/SequenceInterface.h"
#include "PuzzleCharacterBase.generated.h"

class UCameraComponent;

UCLASS(Abstract)
class PROGRAMMINGTEST_API APuzzleCharacterBase : public ACharacter, public ISequenceInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuzzleCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
