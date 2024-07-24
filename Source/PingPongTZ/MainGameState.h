// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

UENUM(BlueprintType)
enum class ETeamEnum : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Red = 1 UMETA(DisplayName = "Red"),
	Blue = 2 UMETA(DisplayName = "Blue")
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

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	//Setter for red and blue teams score
	UFUNCTION(BlueprintCallable)
	void SetTeamScore(ETeamEnum Team, int32 Value);

	//Called when score changed
	//@param Team - in which team score has changed
	//@param Value - new score
	FOnScoreChanged ScoreChangedDelegate;

private:

	UFUNCTION()
	void OnRep_BlueTeamScoreChanged();

	UFUNCTION()
	void OnRep_RedTeamScoreChanged();

	UPROPERTY(ReplicatedUsing = OnRep_BlueTeamScoreChanged)
	int32 BlueTeamScore = 0;

	UPROPERTY(ReplicatedUsing = OnRep_RedTeamScoreChanged)
	int32 RedTeamScore = 0;
};
