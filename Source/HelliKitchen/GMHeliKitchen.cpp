// Fill out your copyright notice in the Description page of Project Settings.


#include "GMHeliKitchen.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void AGMHeliKitchen::BeginPlay()
{
	Super::BeginPlay();

	FindAllActors(GetWorld(), SpawnersList);

	if (SpawnersList.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Spawner Found in the World"));
	}
	else
	{
		SpawnIngredients();
	}

}

void AGMHeliKitchen::SpawnIngredients()
{
	for (int i = 0; i < ToSpawn.Num(); i++)
	{
		SpawnersList[FMath::RandRange(0, SpawnersList.Num() - 1)]->SpawnIngredient(ToSpawn[i]);
	}
}
