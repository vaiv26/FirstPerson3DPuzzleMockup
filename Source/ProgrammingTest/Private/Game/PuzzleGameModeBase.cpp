// Programming Test: underDOGS Studio


#include "Game/PuzzleGameModeBase.h"

#include "Player/PuzzlePlayerController.h"

void APuzzleGameModeBase::PuzzleCompletionEvent()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APuzzlePlayerController* PuzzlePC = Cast<APuzzlePlayerController>(PC);
	if (PuzzlePC)
	{
		PuzzlePC->bPuzzleCompleted = true;
		PuzzlePC->InvokeCompletionEvent();
	}
}
