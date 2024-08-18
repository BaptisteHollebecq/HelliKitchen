// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Props.h"
#include "Spawner.h"
#include "GMHeliKitchen.generated.h"

/**
 * 
 */
UCLASS()
class HELLIKITCHEN_API AGMHeliKitchen : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	void SpawnIngredients();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TArray<ASpawner*> SpawnersList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ingredients")
	TArray<TSubclassOf<AProps>> ToSpawn;
	

private:
	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out);

};

template<typename T>
inline void AGMHeliKitchen::FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}


