// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_PawnTank.h"

// Sets default values
ACPP_PawnTurret::ACPP_PawnTurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPP_PawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTH, this, &ACPP_PawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<ACPP_PawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ACPP_PawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || DistanceToPlayer() > FireRange)
	{
		return;
	}

	Super::RotateTurret(PlayerPawn->GetActorLocation());
}

void ACPP_PawnTurret::CheckFireCondition()
{
	if (PlayerPawn)
	{
		if (DistanceToPlayer() <= FireRange && PlayerPawn->GetPlayerAlive())
		{
			Fire();
		}
	}	
}

float ACPP_PawnTurret::DistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void ACPP_PawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
