// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_HealthComponent.generated.h"

class ACPP_GameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UCPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.0f;
	UPROPERTY()
	float Health = 0.0f;

	ACPP_GameModeBase* GameModeRef;

public:	
	// Sets default values for this component's properties
	UCPP_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
	UFUNCTION()
	void TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstegatedBy, AActor* DamageCauser);
};
