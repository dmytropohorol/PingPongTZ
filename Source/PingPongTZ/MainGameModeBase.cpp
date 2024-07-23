// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "MainPawn.h"
#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "BallActor.h"
#include "MainGameState.h"

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

AActor* AMainGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
	for (AActor* TempActor : PlayerStarts) {
		APlayerStart* PlayerStart = Cast<APlayerStart>(TempActor);
		if (PlayerStart) {
			for (auto Tag : PlayerStart->Tags) {
				if (Tag == "Free") {
					PlayerStart->Tags.Remove("Free");
					PlayerStart->Tags.Add("Occupied");
					return PlayerStart;
				}
			}
		}
	}
	//@Task: if no playerstart found on level do not crush the game
	return nullptr;
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
