// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_PawnBase.generated.h"

class UCapsuleComponent;
class ACPP_ProjectileBase;
class UCPP_HealthComponent;

UCLASS()
class TOONTANKS_API ACPP_PawnBase : public APawn
{
	GENERATED_BODY()

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCPP_HealthComponent* HealthComponent;

	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ACPP_ProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UCameraShake> DeathShake;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DestructionSound;

public:
	// Sets default values for this pawn's properties
	ACPP_PawnBase();

protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();
	virtual void HandleDestruction();
};
