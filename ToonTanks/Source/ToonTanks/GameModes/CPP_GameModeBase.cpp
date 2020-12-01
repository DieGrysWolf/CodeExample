// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameModeBase.h"
#include "ToonTanks/Pawns/CPP_PawnTank.h"
#include "ToonTanks/Pawns/CPP_PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/Cpp_PlayerControllerBase.h"

void ACPP_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<ACPP_PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	if (!PlayerControllerRef)
	{
		PlayerControllerRef = Cast<ACPP_PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	}
	
	HandleGameStart();
}

int32 ACPP_GameModeBase::GetTargetCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_PawnTurret::StaticClass(), TurretActors);

	return TurretActors.Num();
}

void ACPP_GameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetCount();

	//find player pawn by casting
	PlayerTank = Cast<ACPP_PawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));	

	GameStart();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnabledDelegate = FTimerDelegate::CreateUObject
		(
			PlayerControllerRef,
			&ACPP_PlayerControllerBase::SetPlayerEnabledState,
			true
		);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnabledDelegate, StartDelay, false);
	}
}

void ACPP_GameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ACPP_GameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (ACPP_PawnTurret* DestroyedTurret = Cast<ACPP_PawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
		
	}
}
