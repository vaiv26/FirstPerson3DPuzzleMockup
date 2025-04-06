// Programming Test: underDOGS Studio


#include "PuzzleManagers/PuzzleCameraActor.h"
#include "Camera/CameraComponent.h"

// Sets default values
APuzzleCameraActor::APuzzleCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CineCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CineCamera"));
	RootComponent = CineCamera;

}
/*
void APuzzleCameraActor::PlaySequence(APlayerController* PC)
{
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 0.5f;
	TransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_EaseOut;
      
	PC->SetViewTargetWithBlend(
		this,
		TransitionParams.BlendTime,
		TransitionParams.BlendFunction
	);
}
*/
// Called when the game starts or when spawned
void APuzzleCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

