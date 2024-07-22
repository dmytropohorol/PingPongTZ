// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "MainPawn.h"
#include "MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.h"

AMainGameModeBase::AMainGameModeBase()
{
	//Set default controller
	PlayerControllerClass = AMainPlayerController::StaticClass();

	GameStateClass = AMainGameState::StaticClass();

	//Set default pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_MainPawn"));

	if (PlayerPawnBPClass.Class != nullptr){
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
