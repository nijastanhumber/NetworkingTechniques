// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/*
Notes
Client/Server simulation methods
1) Synchronise velocity from the server
2) Overwrite location and rotation from the server
3) Simulate with a fixed time step

Replicated variables: When the replicated variable is set on the server, all the clients will update that same variable with the server's value
*/
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovementReplicationComponent.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	FString GetEnumText(ENetRole role);

	UPROPERTY(VisibleAnywhere)
		UCarMovementComponent *MovementComponent;
	UPROPERTY(VisibleAnywhere)
		UMovementReplicationComponent *MovementReplicator;
};
