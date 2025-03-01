// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongTZ/MainGameState.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:

	UFUNCTION()
	void SpawnNewBall(ETeamEnum Team, int32 Value);

	TSubclassOf<class ABallActor> BallActor;

	FTransform SpawnTransform;

	UPROPERTY()
	class AMainGameState* MainGameState;

	UPROPERTY()
	class AActor* CurrentBallActor;
};
