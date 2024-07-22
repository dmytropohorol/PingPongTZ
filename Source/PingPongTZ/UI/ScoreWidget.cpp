// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "PingPongTZ/MainGameState.h"

void UScoreWidget::WidgetSetup()
{
	UWorld* World = GetWorld();
	if (World) {
		GameState = Cast<class AMainGameState>(World->GetGameState());
		if (GameState) {
			GameState->ScoreChangedDelegate.AddUObject(this, &ThisClass::SetTeamScore);
		}
	}

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
}

void UScoreWidget::SetTeamScore(enum ETeamEnum Team, int32 Value)
{
	switch (Team)
	{
	case ETeamEnum::Red:
		RedTeamScore->SetText(FText::FromString(FString::FromInt(Value))); break;
	case ETeamEnum::Blue:
		BlueTeamScore->SetText(FText::FromString(FString::FromInt(Value))); break;
	}
}