// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Props.h"

#include "Claw.generated.h"

UCLASS()
class HELLIKITCHEN_API AClaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* TriggerVolume;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CatchableInRange = false;
	AProps* InRangeRef;


};
