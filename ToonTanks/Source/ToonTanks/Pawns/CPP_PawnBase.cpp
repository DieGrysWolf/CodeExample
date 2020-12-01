// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/CPP_ProjectileBase.h"
#include "ToonTanks/Components/CPP_HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_PawnBase::ACPP_PawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UCPP_HealthComponent>(TEXT("Health Component"));
}

void ACPP_PawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector CleanLAT = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(CleanLAT - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);	
}

void ACPP_PawnBase::Fire()
{
	if (ProjectileClass)
	{
		ACPP_ProjectileBase* TempProjectile = GetWorld()->SpawnActor<ACPP_ProjectileBase>
			(
			ProjectileClass, 
			ProjectileSpawnPoint->GetComponentLocation(), 
			ProjectileSpawnPoint->GetComponentRotation()
			);		

		TempProjectile->SetOwner(this);
	}
}

void ACPP_PawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}


