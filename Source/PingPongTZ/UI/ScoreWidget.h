// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PINGPONGTZ_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Adding widget to viewport
	UFUNCTION(BlueprintCallable)
	void WidgetSetup();

private:

	UFUNCTION()
	void SetTeamScore(enum ETeamEnum Team, int32 Value);

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RedTeamScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BlueTeamScore;

	UPROPERTY()
	class AMainGameState* GameState;
};
