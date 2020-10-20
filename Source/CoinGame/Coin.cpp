// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	SetRootComponent(Root);
	VisualMesh->SetupAttachment(RootComponent);

	VisualMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	SetActorEnableCollision(true);
	bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

// Spinning and floating visual effect
void ACoin::Spin(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = FMath::Sin(RunningTime * FloatingSpeed) - FMath::Sin((RunningTime - DeltaTime) * FloatingSpeed);

	// Scale the height by the FloatingDistance
	NewLocation.Z += DeltaHeight * FloatingDistance;

	// Rotate by DeltaRotation degrees per second
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotation);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Spin(DeltaTime);
}

