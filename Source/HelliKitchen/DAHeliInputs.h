// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "InputAction.h"

#include "DAHeliInputs.generated.h"

/**
 * 
 */
UCLASS()
class HELLIKITCHEN_API UDAHeliInputs : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputMove;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputLook;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputUp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputDown;
	
};
