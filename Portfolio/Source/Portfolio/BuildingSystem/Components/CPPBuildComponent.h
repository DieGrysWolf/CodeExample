// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPPBuildComponent.generated.h"

class ACPPController;
class ACPPBuilding;
class ACPPBuildCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UCPPBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPPBuildComponent();

	//FUNCTIONS	
	void GhostBuild();	
	void RealBuild();
	void BuildMaster(int Level);
	void SwapBuild();
	void CancelBuild();
	void BuildLocUpdate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//FUNCTIONS
	FVector CalcGridLocation();
	FRotator CalcGridRotation();	

	//VARIABLES
	UPROPERTY()
		ACPPController* PController = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACPPBuilding> BuildFloor;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACPPBuilding> BuildDoorway;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACPPBuilding> BuildWall;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACPPBuilding> BuildWindow;
	UPROPERTY()
		ACPPBuilding* CurrentBuilding = nullptr;
	UPROPERTY()
		FVector PLocation;
	UPROPERTY()
		ACPPBuildCharacter* PCharacter = nullptr;
	UPROPERTY()
		FTimerHandle BuildUpdate;
	UPROPERTY()
		int ChosenBuilding = 0;

};
