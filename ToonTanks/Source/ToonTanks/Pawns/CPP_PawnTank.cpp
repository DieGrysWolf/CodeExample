// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACPP_PawnTank::ACPP_PawnTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	PlayerControllerRef = Cast<APlayerController>(GetController());
	if (!PlayerControllerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerController WTF"));
	}
}

// Called when the game starts or when spawned
void ACPP_PawnTank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACPP_PawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if (!PlayerControllerRef)
	{
		PlayerControllerRef = Cast<APlayerController>(GetController());
	}
	else
	{
		FHitResult TraceHR;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHR);
		FVector HitLocation = TraceHR.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

bool ACPP_PawnTank::GetPlayerAlive()
{
	return bPlayerAlive;
}

// Called to bind functionality to input
void ACPP_PawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPP_PawnTank::MoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_PawnTank::RotateInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACPP_PawnTank::FireWeapon);
}

void ACPP_PawnTank::MoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);	
}

void ACPP_PawnTank::RotateInput(float Value)
{
	FRotator Rotation = FRotator(0, Value * RotateSpeed * GetWorld()->DeltaTimeSeconds, 0);
	RotationDirection = FQuat(Rotation);

}

void ACPP_PawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void ACPP_PawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void ACPP_PawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	bPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ACPP_PawnTank::FireWeapon()
{
	Fire();
}
