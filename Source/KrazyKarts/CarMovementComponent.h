// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float Throttle;
	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;
	UPROPERTY()
		float Time; // time stamp of move

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UCarMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCarMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** The mass of the car */
	UPROPERTY(EditAnywhere)
		float Mass = 1000.0f;

	/** The force applied to the car when the throttle is fully down (N) */
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000.0f;

	/** Minimum radius of the car turning circle at full lock (m) */
	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10.0f;

	/** Higher means more drag. */
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16.0f;

	/** Friction of wheels. Higher means more rolling resistance. */
	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = 0.015f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove &Move);

	FVector GetVelocity() { return Velocity; }
	void SetVelocity(FVector Value) { Velocity = Value; }

	void SetThrottle(float Value) { Throttle = Value; }
	void SetSteeringThrow(float Value) { SteeringThrow = Value; }

	FGoKartMove GetLastMove() { return LastMove; }

private:
	FGoKartMove CreateMove(float DeltaTime);

	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime, float steeringThrow);
	
	FVector Velocity;

	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;
};
