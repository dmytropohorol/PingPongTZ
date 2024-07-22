// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "MainPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SetRootComponent(StaticMeshComponent);
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation((GetActorLocation() + RepVelocity * 100), true);
}

void ABallActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RepVelocity = (RepVelocity - 2*(RepVelocity * Hit.ImpactNormal)*Hit.ImpactNormal).GetSafeNormal();
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABallActor::OnHit);

		//Getting a random starting vector. Using randBool for choosing bigger ranges of numbers are important because if we just use 
		// FRandRange(-1, 1), the vector can get 0 or close to it, and players need to wait a lot of time before the ball will reach them.
		RepVelocity = FVector((FMath::RandBool() ? FMath::FRandRange(-1.f, -0.5f) : FMath::FRandRange(0.5f, 1.f)),
			(FMath::RandBool() ? FMath::FRandRange(-1.f, -0.5f) : FMath::FRandRange(0.5f, 1.f)), 0).GetSafeNormal();
	}
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABallActor, RepVelocity);
}