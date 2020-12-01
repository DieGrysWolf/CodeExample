// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_PawnBase.h"
#include "CPP_PawnTurret.generated.h"

class ACPP_PawnTank;

UCLASS()
class TOONTANKS_API ACPP_PawnTurret : public ACPP_PawnBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRange = 500.0f;

	FTimerHandle FireRateTH;
	ACPP_PawnTank* PlayerPawn = nullptr;

	void CheckFireCondition();
	float DistanceToPlayer();

public:
	ACPP_PawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
};
