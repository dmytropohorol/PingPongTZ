// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainPawn.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PINGPONGTZ_API AMainPawn : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AMainPawn();

	//The pawn speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float PawnSpeed;

	//The maximum distance the pawn can move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float MaxDisnance;

	//The minimum distance the pawn can move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float MinDisnance;

protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server, WithValidation)
	void MoveOnServer(FVector Value);
	void MoveOnServer_Implementation(FVector Value);
	bool MoveOnServer_Validate(FVector Value);

private:

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
};
