// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPlayerComponent.h"

// Sets default values for this component's properties
ULaunchPlayerComponent::ULaunchPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetGenerateOverlapEvents(true);
}

void ULaunchPlayerComponent::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If cast fails this is nullptr
	AMainPawn* MainPawn = Cast<AMainPawn>(OtherActor);

	// This makes sure that the other actor is the player
	if (MainPawn != nullptr)
	{
		MainPawn->CollisionMesh->SetPhysicsLinearVelocity(GetUpVector() * LaunchForce);
	}
}


// Called when the game starts
void ULaunchPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ULaunchPlayerComponent::OnBoxBeginOverlap);
	
}


// Called every frame
void ULaunchPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

