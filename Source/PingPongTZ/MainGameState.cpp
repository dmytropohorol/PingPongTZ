// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"

AMainGameState::AMainGameState()
{
	RedTeamScore = 0;
	BlueTeamScore = 0;
}
int32 AMainGameState::GetTeamScore(ETeamEnum Team) 
{
	switch (Team) {
	case ETeamEnum::Red:
		return RedTeamScore;
	case ETeamEnum::Blue:
		return BlueTeamScore;
	}
	return 0;
}

void AMainGameState::SetTeamScore(ETeamEnum Team, int32 Value)
{
	switch (Team) {
	case ETeamEnum::Red:
		RedTeamScore = Value; break;
	case ETeamEnum::Blue:
		BlueTeamScore = Value; break;
	}
	ScoreChangedDelegate.Broadcast(Team, Value);
}