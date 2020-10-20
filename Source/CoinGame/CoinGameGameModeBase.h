// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoinGameGameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "ItemSpawner.h"
#include "MainPawn.h"
#include "MainPawnState.h"
#include "Templates/SubclassOf.h"
#include "CoinGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COINGAME_API ACoinGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACoinGameGameModeBase();

	UPROPERTY(EditAnywhere)
	float SpawnChance = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthDecrement = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthIncrement = 10.0f;

protected:
	virtual void BeginPlay() override;
	TArray<AActor*> Spawners;

public:
	void OnCollectCoin(AMainPawn* Player, AActor* Coin);
	void SpawnCoins(float DeltaTime);
	void DamageAllPlayers(float Amount);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
