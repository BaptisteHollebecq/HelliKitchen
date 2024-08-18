// Fill out your copyright notice in the Description page of Project Settings.


#include "Claw.h"
#include "Components/BoxComponent.h"
#include "Catchable.h"

// Sets default values
AClaw::AClaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetGenerateOverlapEvents(true);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AClaw::OnBoxBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AClaw::OnBoxEndOverlap);

}

// Called when the game starts or when spawned
void AClaw::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClaw::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCatchable* isCatchable = OtherActor->FindComponentByClass<UCatchable>();

	if (isCatchable != nullptr)
	{
		CatchableInRange = true;
		InRangeRef = Cast<AProps>(OtherActor);
	}
}

void AClaw::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UCatchable* isCatchable = OtherActor->FindComponentByClass<UCatchable>();

	if (isCatchable != nullptr)
	{
		CatchableInRange = false;
		InRangeRef = nullptr;
	}

}



// Called every frame
void AClaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

