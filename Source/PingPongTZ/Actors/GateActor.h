// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongTZ/MainGameState.h"

#include "GateActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class PINGPONGTZ_API AGateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateActor();

	//Executes only on the server, then all important information is replicated in other classes
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* Actor, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ETeamEnum Team;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	UPROPERTY()
	class AMainGameState* GameState;
};
