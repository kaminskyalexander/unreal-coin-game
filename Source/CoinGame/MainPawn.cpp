// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPawn.h"
#include "Coin.h"
#include "CoinGameGameModeBase.h"

// Sets default values
AMainPawn::AMainPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionMesh"));
	VisualMeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VisualMeshRoot"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetRootComponent(CollisionMesh);
	SpringArm->SetupAttachment(RootComponent);
	VisualMeshRoot->SetupAttachment(RootComponent);
	VisualMesh->SetupAttachment(VisualMeshRoot);
	MainCamera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SetActorEnableCollision(true);
	bGenerateOverlapEventsDuringLevelStreaming = true;

	// Disable collision on the visual static mesh in favor of a sphere collider
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualMesh->SetCollisionProfileName(TEXT("IgnoreAll"));

}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMainPawn::OnOverlap);
}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPawn::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount);
}

void AMainPawn::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void AMainPawn::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

void AMainPawn::Pause()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

void AMainPawn::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ACoin* Coin = Cast<ACoin>(OtherActor))
	{
		if(ACoinGameGameModeBase* GM = Cast<ACoinGameGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GM->OnCollectCoin(Cast<AMainPawn>(OverlappedActor), OtherActor);
		}
	}
}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainPawn::Turn);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMainPawn::Pause);
}