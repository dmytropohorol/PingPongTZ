// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

class UFloatingPawnMovement;
class USceneComponent;

UCLASS()
class PINGPONGTZ_API ABallActor : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ABallActor();

	UFUNCTION()
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UPROPERTY(Replicated)
	FVector RepVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
};
