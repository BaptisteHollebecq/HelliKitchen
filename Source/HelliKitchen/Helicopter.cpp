// Fill out your copyright notice in the Description page of Project Settings.


#include "Helicopter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DAHeliInputs.h"
#include "Math/Quat.h"

// Sets default values
AHelicopter::AHelicopter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<UBoxComponent>(TEXT("Origin"));
	SetRootComponent(Origin);


	Body = CreateDefaultSubobject<USceneComponent>(TEXT("BodyOrigin"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Body->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AHelicopter::BeginPlay()
{
	Super::BeginPlay();
	Inertie = FVector(0, 0, 0);
}

// Called every frame
void AHelicopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementDirection.X < StickDeadZone && MovementDirection.X > -StickDeadZone)
		MovementDirection.X = 0;
	if (MovementDirection.Y < StickDeadZone && MovementDirection.Y > -StickDeadZone)
		MovementDirection.Y = 0;

	if (ThrustingDirection != 0)
	{
		ThrustInertie += ThrustingDirection * ThrustingChangingSpeed;
		ThrustInertie = FMath::Clamp(ThrustInertie, -MaxThrusting, MaxThrusting);
	}
	else
	{
		if (ThrustInertie > 0)
			ThrustInertie -= 2 * ThrustingChangingSpeed;
		else if (ThrustInertie < 0)
			ThrustInertie += 2 * ThrustingChangingSpeed;

		if (ThrustInertie <= ThrustingChangingSpeed * 2)
			ThrustInertie = 0;
	}

	Inertie += FVector(0, 0, ThrustInertie);

	if (!MovementDirection.IsZero())
	{
		Inertie += MovementDirection.GetSafeNormal2D() * AccelerationChangingSpeed;
	}
	else
	{
		Inertie -= Inertie.GetSafeNormal() * AccelerationChangingSpeed;

		if (Inertie.Size() <= AccelerationChangingSpeed)
			Inertie = FVector(0, 0, 0);
	}

	Inertie = Inertie.GetClampedToSize(0, MaxAcceleration);

	if (!Inertie.IsZero())
	{
		// movement
		FVector MoveVector = GetActorForwardVector() * Inertie.Y + GetActorRightVector() * Inertie.X + GetActorUpVector() * Inertie.Z;
		FVector NewLocation = GetActorLocation() + (MoveVector * DeltaTime /** CurrentAcceleration*/);
		SetActorLocation(NewLocation, true);

		//orientation
		const FVector planeInertie = FVector(Inertie.X, Inertie.Y, 0);
		LeaningDirection = Inertie.GetSafeNormal2D();
		LeaningDirection.X *= -1;
		Body->SetRelativeRotation(GetRotatorFromAxisAndAngle(LeaningDirection, (planeInertie.Size() / MaxAcceleration) * MaxAngle));
	}

}

// Called to bind functionality to input
void AHelicopter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(CharacterMappingContext, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(DAHelicoInputs->InputMove, ETriggerEvent::Triggered, this, &AHelicopter::Move);
	PEI->BindAction(DAHelicoInputs->InputMove, ETriggerEvent::Canceled, this, &AHelicopter::StopMove);
	PEI->BindAction(DAHelicoInputs->InputMove, ETriggerEvent::Completed, this, &AHelicopter::StopMove);

	PEI->BindAction(DAHelicoInputs->InputLook, ETriggerEvent::Triggered, this, &AHelicopter::Look);

	PEI->BindAction(DAHelicoInputs->InputUp, ETriggerEvent::Started, this, &AHelicopter::StartUp);
	PEI->BindAction(DAHelicoInputs->InputUp, ETriggerEvent::Canceled, this, &AHelicopter::StopUp);
	PEI->BindAction(DAHelicoInputs->InputUp, ETriggerEvent::Completed, this, &AHelicopter::StopUp);

	PEI->BindAction(DAHelicoInputs->InputDown, ETriggerEvent::Started, this, &AHelicopter::StopUp);
	PEI->BindAction(DAHelicoInputs->InputDown, ETriggerEvent::Canceled, this, &AHelicopter::StartUp);
	PEI->BindAction(DAHelicoInputs->InputDown, ETriggerEvent::Completed, this, &AHelicopter::StartUp);
}

void AHelicopter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		MovementDirection = Value.Get<FVector>();
	}
}

void  AHelicopter::StopMove()
{
	MovementDirection = FVector(0, 0, 0);
}

void AHelicopter::StartUp()
{
	ThrustingDirection += 1;
}

void AHelicopter::StopUp()
{
	ThrustingDirection -= 1;
}

void AHelicopter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X * TurnSpeed);
		}

		if (LookValue.Y != 0.f)
		{
			float Rotation = SpringArm->GetRelativeRotation().Pitch + LookValue.Y;

			if (Rotation < CameraClamp.Y && Rotation > CameraClamp.X)
			{
				SpringArm->AddLocalRotation(FRotator(LookValue.Y, 0, 0));
			}
		}
	}
}

FRotator AHelicopter::GetRotatorFromAxisAndAngle(const FVector& Axis, float AngleInDegrees)
{
	// Assurez-vous que l'axe est normalisé
	FVector NormalizedAxis = Axis.GetSafeNormal();

	// Convertir l'angle de degrés en radians
	float AngleInRadians = FMath::DegreesToRadians(AngleInDegrees);

	// Créer un quaternion à partir de l'axe et de l'angle
	FQuat QuatRotation = FQuat(NormalizedAxis, AngleInRadians);

	// Convertir le quaternion en rotator
	FRotator RotatorResult = QuatRotation.Rotator();

	return RotatorResult;
}
