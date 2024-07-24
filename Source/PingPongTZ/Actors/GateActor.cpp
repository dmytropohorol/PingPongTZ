// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "PingPongTZ/BallActor.h"
#include "PingPongTZ/MainGameState.h"

// Sets default values
AGateActor::AGateActor()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionBox"));
	SetRootComponent(CollisionBox);
}

void AGateActor::OnBoxOverlap(UPrimitiveComponent* Actor, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABallActor>(OtherActor)) {
		if (GameState) {
			GameState->SetTeamScore(Team, GameState->GetTeamScore(Team) + 1);
		}
	}
}

// Called when the game starts or when spawned
void AGateActor::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGateActor::OnBoxOverlap);
		UWorld* World = GetWorld();
		if (World) {
			GameState = Cast<class AMainGameState>(World->GetGameState());
		}
	}
}