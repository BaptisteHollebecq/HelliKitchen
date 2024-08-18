// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Catchable.h"

#include "Props.generated.h"

UCLASS()
class HELLIKITCHEN_API AProps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PropsMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ManagePhysics(bool physic);

};
