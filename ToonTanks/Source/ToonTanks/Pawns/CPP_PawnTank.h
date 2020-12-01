// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_PawnBase.h"
#include "CPP_PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API ACPP_PawnTank : public ACPP_PawnBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera = nullptr;

	FVector MoveDirection;
	FQuat RotationDirection;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite , Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0;

	APlayerController* PlayerControllerRef = nullptr;
	bool bPlayerAlive = true;

	void MoveInput(float Value);
	void RotateInput(float Value);

	void Move();
	void Rotate();

	void FireWeapon();

public:
	ACPP_PawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetPlayerAlive();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
