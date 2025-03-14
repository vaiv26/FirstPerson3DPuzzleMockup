// Programming Test: underDOGS Studio

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SequenceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USequenceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to store camera sequences
 */
class PROGRAMMINGTEST_API ISequenceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void PlaySequence(APlayerController* PC);
};
