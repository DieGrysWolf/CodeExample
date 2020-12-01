// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPPBuildCharacter.generated.h"

//forward declare
class UCameraComponent;
class UEnum;
class ACPPController;
class UCPPBuildComponent;

UCLASS()
class PORTFOLIO_API ACPPBuildCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPPBuildCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//FUNCTIONS
	UFUNCTION()
		void ChangeState();

	//FVector GetLocation();

	//VARIABLES
	UPROPERTY()
		UEnum* StateEnum = nullptr;
	UPROPERTY()
		int CurrentState;
	UPROPERTY()
		ACPPController* PController = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCPPBuildComponent* Builder = nullptr;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* FPCamera = nullptr;

	UPROPERTY(BlueprintReadWrite)
		int BuildingIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	//FUNCTIONS
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void DisplayRadial();
	UFUNCTION()
		void Build();
	
};
