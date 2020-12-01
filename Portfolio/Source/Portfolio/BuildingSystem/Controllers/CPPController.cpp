// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPController.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Portfolio/BuildingSystem/Instances/CPPGameInstance.h"

#define OUT

// Called when the game starts or when spawned
void ACPPController::BeginPlay()
{
	Super::BeginPlay();

	//cast and set game instance
	GameInstance = Cast<UCPPGameInstance>(GetGameInstance());
	if (!GameInstance){	GameInstance = Cast<UCPPGameInstance>(GetGameInstance()); }

	//does what you think
	HUD->AddToViewport();
}

void ACPPController::ToggleBuildRadial()
{
	//check if radial already exists
	if (!RadialActive)
	{	
		//change input mode
		FInputModeGameAndUI InputMode;
		this->SetInputMode(InputMode);

		//add widget and allow mouse to control
		BuildRadial->AddToViewport();
		this->bShowMouseCursor = true;
		RadialActive = true;

		//moves mouse to center so player can build faster once comfortable
		CenterMouse();
		return;
	}
	else if (RadialActive)		
	{
		//change input mode
		FInputModeGameOnly InputMode;
		this->SetInputMode(InputMode);

		//remove widget and remove mouse control
		BuildRadial->RemoveFromViewport();
		this->bShowMouseCursor = false;
		RadialActive = false;

		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Radial Index: %s"), *FString::FromInt(RadialIndex));
}

void ACPPController::CenterMouse()
{
	//initialize and assign x and y values
	int XValue;
	int YValue;
	GetViewportSize(OUT XValue, OUT YValue);

	//set location using half screen dimensions for center
	SetMouseLocation(XValue/2, YValue/2);
}

int ACPPController::GetRadialIndex()
{
	return RadialIndex;
}
