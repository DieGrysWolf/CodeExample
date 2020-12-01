// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBuildComponent.h"
#include "Portfolio/BuildingSystem/Controllers/CPPController.h"
#include "Math/UnrealMathUtility.h"
#include "Portfolio/BuildingSystem/Actors/CPPBuilding.h" //WIP
#include "Portfolio/BuildingSystem/Characters/CPPBuildCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCPPBuildComponent::UCPPBuildComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void UCPPBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	//cast and set player controller
	PController = Cast<ACPPController>(GetOwner()->GetInstigatorController());
	if (!PController){ PController = Cast<ACPPController>(GetOwner()->GetInstigatorController()); }

	//cast and set player character
	PCharacter = Cast<ACPPBuildCharacter>(GetOwner());

	//UE_LOG(LogTemp, Warning, TEXT("Character %s"), *PCharacter->GetName())
}

void UCPPBuildComponent::GhostBuild()
{
	//set building level 1
	BuildMaster(0);

	if (PController)
	{
		//create timer while in build mode
		GetWorld()->GetTimerManager().SetTimer(BuildUpdate, this, &UCPPBuildComponent::BuildLocUpdate, 0.1, true);
	}
}

void UCPPBuildComponent::RealBuild()
{
	//remove timer
	GetWorld()->GetTimerManager().ClearTimer(BuildUpdate);
	BuildUpdate.Invalidate();

	//destroy current actor
	CurrentBuilding->Destroy();
		
	//create new actor, change level and create new ghost actor after placement
	BuildMaster(1);
	GhostBuild();
}

void UCPPBuildComponent::BuildMaster(int Level)
{
	FActorSpawnParameters SpawnParams;

	if (Level != 0)
	{
		SpawnParams;
	}

	//test radial index agains values and perform different task
	//creates actor and sets level
	switch (PController->GetRadialIndex())
	{
	case 1:
		//UE_LOG(LogTemp, Error, TEXT("Built: Floor"));
		CurrentBuilding = GetWorld()->SpawnActor<ACPPBuilding>(BuildFloor, CalcGridLocation(), CalcGridRotation());
		CurrentBuilding->ChangeLevel(Level);
		break;
	case 2:
		//UE_LOG(LogTemp, Error, TEXT("Built: Doorway"));
		CurrentBuilding = GetWorld()->SpawnActor<ACPPBuilding>(BuildDoorway, CalcGridLocation(), CalcGridRotation());
		CurrentBuilding->ChangeLevel(Level);
		break;
	case 3:
		//UE_LOG(LogTemp, Error, TEXT("Built: Wall"));
		CurrentBuilding = GetWorld()->SpawnActor<ACPPBuilding>(BuildWall, CalcGridLocation(), CalcGridRotation());
		CurrentBuilding->ChangeLevel(Level);
		break;
	case 4:
		//UE_LOG(LogTemp, Error, TEXT("Built: Window"));
		CurrentBuilding = GetWorld()->SpawnActor<ACPPBuilding>(BuildWindow, CalcGridLocation(), CalcGridRotation());
		CurrentBuilding->ChangeLevel(Level);
		break;
	default:
		break;
	}	
}

void UCPPBuildComponent::SwapBuild()
{
	//remove timer
	GetWorld()->GetTimerManager().ClearTimer(BuildUpdate);
	BuildUpdate.Invalidate();

	//check current building valid
	if (CurrentBuilding)
	{
		//destory and clear variable
		CurrentBuilding->Destroy();
		CurrentBuilding = nullptr;
	}	

	//create new ghost actor
	GhostBuild();
}

void UCPPBuildComponent::CancelBuild()
{
	//remove timer
	GetWorld()->GetTimerManager().ClearTimer(BuildUpdate);
	BuildUpdate.Invalidate();

	//remove any ghost buildings from screen
	if (CurrentBuilding && CurrentBuilding != nullptr)
	{
		//destory and clear variable
		CurrentBuilding->Destroy();
		CurrentBuilding = nullptr;
	}
}

FVector UCPPBuildComponent::CalcGridLocation()
{
	//set local variables
	int GridXY = 400;
	int GridZ = 300;
	float ForwardOffset = 200;
	FVector Location;
	FVector PlayerLocation = PCharacter->GetActorLocation();

	//get players yaw rotation
	float Value = (PCharacter->FPCamera->GetComponentRotation().Yaw);

	//check player rotation and change forwardoffset accordingly 
	//(this doesn't work perfect, WORK ON)
	if (Value > -45.0f && Value < 45.0f) //this is +X (forward)
	{
		//set created actor location on a offset of players location
		Location = FVector(PlayerLocation.X + ForwardOffset, PlayerLocation.Y + (ForwardOffset * 1000), PlayerLocation.Z);
		//UE_LOG(LogTemp, Error, TEXT("Actor Facing Forward"));
	}	
	if (Value >= 45.0f && Value <= 135.0f) //this is +Y (right)
	{
		//set created actor location on a offset of players location
		Location = FVector(PlayerLocation.X - (ForwardOffset * 2), PlayerLocation.Y, PlayerLocation.Z);
		//UE_LOG(LogTemp, Error, TEXT("Actor Facing Right"));
	}
	if (Value > 135.0f || Value < -135.0f) //this is -X (reverse)
	{
		//set created actor location on a offset of players location
		Location = FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
		//UE_LOG(LogTemp, Error, TEXT("Actor Facing Backwards"));
	}
	if (Value <= -45.0f && Value >= -135.0f) //this is -X (left) ..WORKS
	{
		//set created actor location on a offset of players location
		Location = FVector(PlayerLocation.X, PlayerLocation.Y - ForwardOffset, PlayerLocation.Z);
		//UE_LOG(LogTemp, Error, TEXT("Actor Facing Left"));
	}
	else
	{
		//set actor location to a basic location
		//should never get here but just added in case
		Location = FVector(PlayerLocation.X + ForwardOffset, PlayerLocation.Y, PlayerLocation.Z);
	}

	//generate grid to place actor based on the offset location by normalising
	int VectorX = ((FMath::RoundToInt(Location.X / GridXY)) * GridXY);
	int VectorY = ((FMath::RoundToInt(Location.Y / GridXY)) * GridXY);
	int VectorZ = ((FMath::RoundToInt(Location.Z / GridZ)) * GridZ);
	
	return FVector(VectorX, VectorY, VectorZ) + FVector(0, 0, 20);
}

FRotator UCPPBuildComponent::CalcGridRotation()
{	
	//set local variables
	int Rotation = 90;
	int RotationOffset = 270;

	//get player rotation
	float Value = (PCharacter->FPCamera->GetComponentRotation().Yaw);

	//return player rotation normalized
	return FRotator(0, ((FMath::RoundToInt(Value / Rotation)) * Rotation) + RotationOffset, 0);	
}

//called by the timer in GhostBuild()
void UCPPBuildComponent::BuildLocUpdate()
{
	CurrentBuilding->SetActorLocationAndRotation(CalcGridLocation(), CalcGridRotation());

	//UE_LOG(LogTemp, Warning, TEXT("Location = %s"), *PCharacter->FPCamera->GetForwardVector().ToString())
	//UE_LOG(LogTemp, Warning, TEXT("Location = %s"), *CalcGridLocation().ToString())
	//UE_LOG(LogTemp, Warning, TEXT("Rotation = %s"), *CalcGridRotation().ToString())
}


