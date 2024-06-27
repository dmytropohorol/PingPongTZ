// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"
#include "MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InputAction.h"

// Sets default values
AMainPawn::AMainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant = true;
	bReplicates = true;

	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("PawnMovementComponent"));
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMainPawn::Move(const FInputActionValue& Value)
{
	// input is a float
	const float MovementValue = Value.Get<float>();

	if (Controller != nullptr)
	{
		// get location and direction
		FVector Location = GetActorLocation();
		FVector Direction = GetActorForwardVector();

		// clamping and applying movement
		Location.Y = FMath::Clamp( (GetActorLocation().Y + ((-1 * Direction.X) * (MovementValue * PawnSpeed))), MinDisnance, MaxDisnance);
		HasAuthority() ? Multicast_Move(Location) : Server_Move(Location);
	}
}

void AMainPawn::Server_Move_Implementation(const FVector Value)
{
	Multicast_Move(Value);
}

void AMainPawn::Multicast_Move_Implementation(const FVector Value)
{
	SetActorLocation(Value, false);
}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPawn::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

