// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Components/BoxComponent.h>

#include "Helicopter.generated.h"

UCLASS()
class HELLIKITCHEN_API AHelicopter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHelicopter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HelicoSettings | Inputs")
	class UInputMappingContext* CharacterMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Inputs")
	class UDAHeliInputs* DAHelicoInputs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Inputs")
	float StickDeadZone = .3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float MaxAngle = 45;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float MaxAcceleration = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float AccelerationChangingSpeed = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float MaxThrusting = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float ThrustingChangingSpeed = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float TurnSpeed = .75f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	float BladeSpeed = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HelicoSettings | Properties")
	FVector2D CameraClamp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Body;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* LargeBlade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SmallBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Origin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* Camera;

private:

	FVector MovementDirection;
	FVector Inertie;
	FVector LeaningDirection;
	float ThrustInertie;
	float ThrustingDirection;
	float CurrentAcceleration = 0;
	float BladeTurningRotator;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handle move input
	void Move(const FInputActionValue& Value);

	void StopMove();
	void StartUp();
	void StopUp();

	// Handle look input
	void Look(const FInputActionValue& Value);

	FRotator GetRotatorFromAxisAndAngle(const FVector& Axis, float AngleInDegrees);

};
