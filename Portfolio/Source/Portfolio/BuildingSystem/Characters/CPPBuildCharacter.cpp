// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBuildCharacter.h"
#include "Camera/CameraComponent.h"
#include "Portfolio/BuildingSystem/Data/CPPStates.h"
#include "Portfolio/BuildingSystem/Controllers/CPPController.h"
#include "Portfolio/BuildingSystem/Components/CPPBuildComponent.h"

// Sets default values
ACPPBuildCharacter::ACPPBuildCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create, initialise and root player camera
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCamera->SetupAttachment(RootComponent);
	FPCamera->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	FPCamera->bUsePawnControlRotation = true;

	//find enum
	StateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECPPStates"), true);	
}

// Called when the game starts or when spawned
void ACPPBuildCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//set players current state
	CurrentState = ECPPStates::STATE_Passive;

	//cast anbd set player controller
	PController = Cast<ACPPController>(GetController());
	if (!PController) { PController = Cast<ACPPController>(GetController()); }

	//get build component on player
	Builder = FindComponentByClass<UCPPBuildComponent>();
}

// Called to bind functionality to input
void ACPPBuildCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	//move player
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPPBuildCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPPBuildCharacter::MoveRight);

	//move camera
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	//setup actions
	PlayerInputComponent->BindAction("ChangeState", IE_Pressed, this, &ACPPBuildCharacter::ChangeState);			//change player state between passive and build
	PlayerInputComponent->BindAction("DisplayBuildRadial", IE_Pressed, this, &ACPPBuildCharacter::DisplayRadial);	//show build radial
	PlayerInputComponent->BindAction("DisplayBuildRadial", IE_Released, this, &ACPPBuildCharacter::DisplayRadial);	//hide build radial
	PlayerInputComponent->BindAction("LeftAction", IE_Pressed, this, &ACPPBuildCharacter::Build);					//place actor
}

void ACPPBuildCharacter::MoveForward(float Value)
{
	//runs only if valid value
	if (Value != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}	
}

void ACPPBuildCharacter::MoveRight(float Value)
{
	//runs only if valid value
	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACPPBuildCharacter::ChangeState()
{	
	//check player state
	if (CurrentState == ECPPStates::STATE_Passive)
	{
		CurrentState = ECPPStates::STATE_Build;

		//call method in CPPBuildComponent
		Builder->GhostBuild();

		//UE_LOG(LogTemp, Warning, TEXT("Player is in: Build Mode"));
	}
	else if (CurrentState == ECPPStates::STATE_Build)
	{
		CurrentState = ECPPStates::STATE_Passive;

		//call method in CPPBuildComponent
		Builder->CancelBuild();

		//UE_LOG(LogTemp, Warning, TEXT("Player is in: Passive Mode"));
	}
}

void ACPPBuildCharacter::DisplayRadial()
{
	if (CurrentState == ECPPStates::STATE_Build)
	{
		//call method in CPPController
		PController->ToggleBuildRadial();

		//call method in CPPBuildComponent
		Builder->SwapBuild();
	}
}

void ACPPBuildCharacter::Build()
{
	if (CurrentState == ECPPStates::STATE_Build && Builder)
	{
		//call method in CPPBuildComponent
		Builder->RealBuild();
	}	
}



