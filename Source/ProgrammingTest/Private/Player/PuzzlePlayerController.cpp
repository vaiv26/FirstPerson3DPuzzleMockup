// Programming Test: underDOGS Studio


#include "Player/PuzzlePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/SequenceInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleManagers/PuzzleBoard.h"
#include "PuzzleManagers/PuzzleCameraActor.h"
#include "PuzzlePieces/PuzzleCrescentPiece.h"

APuzzlePlayerController::APuzzlePlayerController()
{
	CurrentPawn = 0;
	NextPawn = 0;
	CooldownTime = 5.0f;
	bCanPerformAction = true;
}


void APuzzlePlayerController::SwitchAndPossess()
{
	if (bPuzzleCompleted) return;
	if (FoundPawns.Num() > 0)
	{
		SwitchToNextPuzzlePiece();
	}
	if (ISequenceInterface* SequenceInterface = Cast<ISequenceInterface>(UGameplayStatics::GetActorOfClass(GetWorld(), FixedCameraComponent)))
	{
		SequenceInterface->PlaySequence(this);
	}
}

void APuzzlePlayerController::ResetCooldown()
{
	bCanPerformAction = true;
}

void APuzzlePlayerController::DrawPawnHighlight(APawn* TargetPawn, FColor Color)
{
	if (TargetPawn)
	{
		DrawDebugSphere(
			GetWorld(),
			TargetPawn->GetActorLocation(),
			5.0f,  
			12,      
			FColor::Red,
			false,   
			2.f,    
			0,       
			5.0f     
		);
	}
}

void APuzzlePlayerController::SwitchToNextPuzzlePiece()
{
	if (!bCanPerformAction)
	{
		return;
	}
	if (FoundPawns.Num() > 0)
	{
		UnPossess();
		NextPawn = (CurrentPawn + 1) % FoundPawns.Num();
		Possess(FoundPawns[NextPawn]);
		DrawPawnHighlight(FoundPawns[NextPawn], FColor::Red);
		CurrentPawn = NextPawn;
		bAutoManageActiveCameraTarget = false;
	}
	bCanPerformAction = false;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &APuzzlePlayerController::ResetCooldown, CooldownTime, false);
}

void APuzzlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	FirstPerson = GetPawn();
	check(PuzzleContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PuzzleContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// Getting the Pawns
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleCrescentPiece::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		APuzzleCrescentPiece* Puzzlepiece = Cast<APuzzleCrescentPiece>(Actor);
		if (Puzzlepiece)
		{
			FoundPawns.Add(Puzzlepiece);
		}
	}

	if (AActor* PuzzleBoardActor = UGameplayStatics::GetActorOfClass(GetWorld(), APuzzleBoard::StaticClass()))
	{
		if (APuzzleBoard* PuzzleBoard = Cast<APuzzleBoard>(PuzzleBoardActor))
		{
			PuzzleBoard->OnPuzzleCompleted.BindUObject(this, &APuzzlePlayerController::InvokeCompletionEvent);
		}
	}
}

void APuzzlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APuzzlePlayerController::Move);

	EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered,this,&APuzzlePlayerController::SwitchToNextPuzzlePiece);
	
}

void APuzzlePlayerController::Move(const struct FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void APuzzlePlayerController::InvokeCompletionEvent()
{
	bAutoManageActiveCameraTarget = true;
	UnPossess();
	Possess(FirstPerson);
}


