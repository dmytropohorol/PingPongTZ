// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

UENUM(BlueprintType)
enum class ETeamEnum : uint8 {
	Red = 0 UMETA(DisplayName = "Red"),
	Blue = 1 UMETA(DisplayName = "Blue")
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, ETeamEnum Team, int32 Value)

/**
 * 
 */
UCLASS()
class PINGPONGTZ_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	AMainGameState();

	//Getter for red and blue teams score
	UFUNCTION(BlueprintCallable)
	int32 GetTeamScore(ETeamEnum Team);

	//Setter for red and blue teams score
	UFUNCTION(BlueprintCallable)
	void SetTeamScore(ETeamEnum Team, int32 Value);

	//Called when score changed
	//@param Team - in which team score has changed
	//@param Value - new score
	FOnScoreChanged ScoreChangedDelegate;

private:

	UPROPERTY()
	int32 BlueTeamScore = 0;

	UPROPERTY()
	int32 RedTeamScore = 0;
};
