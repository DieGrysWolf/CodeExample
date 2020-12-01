// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPBuilding.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACPPBuilding::ACPPBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create and root scenecomponent
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	//create and root static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);	
}

// Called when the game starts or when spawned
void ACPPBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	//give initial values
	BuildStruct.Level = 0;
	ChangeLevel(BuildStruct.Level);
}

//called in blueprints as well
void ACPPBuilding::ChangeLevel_Implementation(int Value)
{
	//test value's value and applies the correct material
	//this allows a later creation of a building upgrade system
	switch (Value)
	{
	case 0:
		StaticMesh->SetMaterial(0, GhostMat);
		break;
	case 1:
		StaticMesh->SetMaterial(0, WoodMat);
		break;
	case 2:
		StaticMesh->SetMaterial(0, StoneMat);
		break;
	case 3:
		StaticMesh->SetMaterial(0, IronMat);
		break;
	default:
		break;
	}
}

