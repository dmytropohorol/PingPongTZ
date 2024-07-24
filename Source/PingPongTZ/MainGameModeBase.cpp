// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "MainPawn.h"
#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "BallActor.h"
#include "MainGameState.h"
#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"

AMainGameModeBase::AMainGameModeBase()
{
	//Set default controller
	PlayerControllerClass = AMainPlayerController::StaticClass();

	GameStateClass = AMainGameState::StaticClass();

	SpawnTransform.SetLocation(FVector(0,0,-350));

	//Set default pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_MainPawn"));

	static ConstructorHelpers::FClassFinder<ABallActor> BallActorBPClass(TEXT("/Game/Blueprints/BP_BallActor"));

	if (BallActorBPClass.Class != nullptr) {
		BallActor = BallActorBPClass.Class;
	}

	if (PlayerPawnBPClass.Class != nullptr){
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMainGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetNumPlayers() == 2) {
		UWorld* World = GetWorld();
		if (World) {
			MainGameState = Cast<class AMainGameState>(World->GetGameState());
			if (MainGameState) {
				MainGameState->ScoreChangedDelegate.AddUObject(this, &ThisClass::SpawnNewBall);
			}
			if (BallActor != nullptr) {
				CurrentBallActor = World->SpawnActor(BallActor, &SpawnTransform);
			}
		}
	}
}

void AMainGameModeBase::Logout(AController* Exiting)
{
	UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		for (FName Tag : PlayerStart->Tags) {
			if (Tag == FName(Exiting->GetName())) {
				PlayerStart->Tags.Remove(FName(Exiting->GetName()));
				PlayerStart->Tags.Add("Free");
				goto Logout;
			}
		}
	}
	Logout:
	Super::Logout(Exiting);
}

AActor* AMainGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	APlayerStart* FoundPlayerStart = nullptr;
	UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		// If no PlayerStarts avaiable (it is not expected to be more than two players, but we don't want to have a crash), 
		// just getting the first one
		FoundPlayerStart = PlayerStart;
		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			FoundPlayerStart = PlayerStart;
			goto ReturnFounded;
		}
		else
		{
			// Checking for "Free" tag, if found one, adding occupied tag and spawning there player
			for (auto Tag : PlayerStart->Tags) {
				if (Tag == "Free") {
					PlayerStart->Tags.Remove("Free");
					PlayerStart->Tags.Add(FName(Player->GetName()));
					FoundPlayerStart = PlayerStart;
					goto ReturnFounded;
				}
			}
		}
	}
	ReturnFounded:
	return FoundPlayerStart;
}

void AMainGameModeBase::SpawnNewBall(ETeamEnum Team, int32 Value)
{
	UWorld* World = GetWorld();
	if (World) {
		if (BallActor != nullptr) {
			if (CurrentBallActor != nullptr) {
				CurrentBallActor->Destroy();
			}
			CurrentBallActor = World->SpawnActor(BallActor, &SpawnTransform);
		}
	}
}
