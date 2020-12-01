// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HealthComponent.h"
#include "ToonTanks/GameModes/CPP_GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCPP_HealthComponent::UCPP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;

	GameModeRef = Cast<ACPP_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCPP_HealthComponent::TakeDamage);
	
}

void UCPP_HealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstegatedBy, AActor* DamageCauser)
{
	if (Damage != 0.0f && Health >= 0.1f)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

		if (Health <= 0)
		{
			if (GameModeRef)
			{
				GameModeRef->ActorDied(GetOwner());
			}			
		}
	}
}

