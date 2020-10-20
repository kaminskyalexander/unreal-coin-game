// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "CoinGameGameModeBase.h"
#include "CoinGameGameStateBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ACoinGameGameModeBase::ACoinGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinGameGameModeBase::OnCollectCoin(AMainPawn* Player, AActor* Coin)
{
	// Get MainPawnState of MainPawn that collected the coin
	if (AMainPawnState* PlayerState = Cast<AMainPawnState>(Player->GetPlayerState()))
	{
		if (!PlayerState->Dead)
		{
			// Destroy the collected coin
			Coin->Destroy();

			// Increment health
			PlayerState->CurrentHealth = FMath::Clamp(PlayerState->CurrentHealth + HealthIncrement, 0.0f, PlayerState->MaximumHealth);

			// Increment score
			PlayerState->SetScore(PlayerState->GetScore() + 1.0f);
		}
	}
}

void ACoinGameGameModeBase::SpawnCoins(float DeltaTime)
{
	// Loop over all spawner nodes in the level
	if(ACoinGameGameStateBase* GS = Cast<ACoinGameGameStateBase>(GetWorld()->GetGameState()))
	{
		if(GS->GameStarted)
		{
			for (AActor* Spawner : Spawners)
			{
				if (FMath::FRand() < SpawnChance * DeltaTime)
				{
					// Cast to ItemSpawner for method
					if (AItemSpawner* MySpawner = Cast<AItemSpawner>(Spawner))
					{
						// Call spawn method on node
						MySpawner->SpawnCoin();
					}
				}
			}
		}
	}
}

void ACoinGameGameModeBase::DamageAllPlayers(float Amount)
{
	// Get current game state
	if (ACoinGameGameStateBase* GS = Cast<ACoinGameGameStateBase>(GetWorld()->GetGameState()))
	{
		// If Game Started
		if(GS->GameStarted)
		{
			// Loop over all player states
			for (APlayerState* PlayerState : GS->PlayerArray)
			{
				// Cast player state to AMainPawnState
				if (AMainPawnState* MainPawnState = Cast<AMainPawnState>(PlayerState))
				{
					// Decrease health by desired amount, clamping it at zero
					MainPawnState->CurrentHealth = FMath::Clamp(MainPawnState->CurrentHealth - Amount, 0.0f, MainPawnState->MaximumHealth);
				}
			}
		}
	}
}

void ACoinGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Find all item spawner nodes
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawner::StaticClass(), Spawners);
}

void ACoinGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SpawnCoins(DeltaTime);
	DamageAllPlayers(HealthDecrement * DeltaTime);
}
