// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPController.generated.h"

//forward declare
class UCPPGameInstance;
class UUserWidget;

UCLASS()
class PORTFOLIO_API ACPPController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//VARIABLES
	UPROPERTY()
		UCPPGameInstance* GameInstance = nullptr;
	UPROPERTY()
		bool RadialActive = false;

public:

	//FUNCTIONS
	UFUNCTION()
		void ToggleBuildRadial();
	UFUNCTION()
		void CenterMouse();
	UFUNCTION()
		int GetRadialIndex();	

	//VARIABLES
	UPROPERTY(BlueprintReadWrite)
		int RadialIndex = 1;		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* BuildRadial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* HUD;
	
};
