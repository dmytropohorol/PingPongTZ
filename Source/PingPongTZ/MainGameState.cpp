// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Net/UnrealNetwork.h"

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
	case ETeamEnum::None:
		break;
	}
	return 0;
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, BlueTeamScore);
	DOREPLIFETIME(AMainGameState, RedTeamScore);
}

void AMainGameState::SetTeamScore(ETeamEnum Team, int32 Value)
{
	switch (Team) {
	case ETeamEnum::Red:
		RedTeamScore = Value; break;
	case ETeamEnum::Blue:
		BlueTeamScore = Value; break;
	case ETeamEnum::None: 
		return;
	}
	//Executes only on the server. TeamScore variables are replicated for notifying clients about changing their scores in ScoreWidget. 
	// Notified on server too, because game mode is server-authoritative and handles all game logic, in that case, destroying and creating balls.
	ScoreChangedDelegate.Broadcast(Team, Value);
}

void AMainGameState::OnRep_BlueTeamScoreChanged()
{
	ScoreChangedDelegate.Broadcast(ETeamEnum::Blue, BlueTeamScore);
}

void AMainGameState::OnRep_RedTeamScoreChanged()
{
	ScoreChangedDelegate.Broadcast(ETeamEnum::Red, RedTeamScore);
}