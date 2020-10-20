// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class COINGAME_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float FloatingSpeed;

	UPROPERTY(EditAnywhere)
	float FloatingDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Spin(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
