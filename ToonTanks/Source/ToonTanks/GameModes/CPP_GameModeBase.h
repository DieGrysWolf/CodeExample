// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameModeBase.generated.h"

class ACPP_PawnTurret;
class ACPP_PawnTank;
class ACPP_PlayerControllerBase;

UCLASS()
class TOONTANKS_API ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	ACPP_PawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	ACPP_PlayerControllerBase* PlayerControllerRef;

	int32 GetTargetCount();
	
	UFUNCTION()
	void HandleGameStart();
	UFUNCTION()
	void HandleGameOver(bool PlayerWon);

public:

	void ActorDied(AActor* DeadActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};
