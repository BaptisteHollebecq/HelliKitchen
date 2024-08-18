// Fill out your copyright notice in the Description page of Project Settings.


#include "Props.h"

// Sets default values
AProps::AProps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PropsMesh = CreateDefaultSubobject<UStaticMeshComponent>("PropsMesh");
	SetRootComponent(PropsMesh);

	ManagePhysics(true);

	CreateDefaultSubobject<UCatchable>(TEXT("CatchMe"));
}

// Called when the game starts or when spawned
void AProps::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProps::ManagePhysics(bool physic)
{
	PropsMesh->SetSimulatePhysics(physic);
}

