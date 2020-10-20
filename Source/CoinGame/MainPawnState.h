// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPawnState.generated.h"

UCLASS()
class COINGAME_API AMainPawnState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaximumHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = MaximumHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool Dead = false;
	
};
