// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "MainPawn.h"

// Sets default values
ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	BallSpeed = 100.f;
	Velocity = FVector(0.f, 0.f, 0.f);

	SetReplicateMovement(true);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ABallActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AMainPawn>(OtherActor)) {
		Velocity.X *= -1;
	}
	else {
		Velocity.Y *= -1;
	}
}

void ABallActor::Move()
{
	SetActorLocation((GetActorLocation() + Velocity * BallSpeed), true);
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABallActor::OnHit);

	FMath::RandBool() ? Velocity.X = -1.f : Velocity.X = 1.f;
	FMath::RandBool() ? Velocity.Y = -1.f : Velocity.Y = 1.f;
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABallActor, Velocity);
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

