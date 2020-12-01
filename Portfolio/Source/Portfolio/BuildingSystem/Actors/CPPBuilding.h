// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPBuilding.generated.h"

class UStaticMeshComponent;

//struct used for actors to be created in the system
USTRUCT()
struct FBuildStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int Index;	
	UPROPERTY(EditAnywhere)
		int Level;
};

UCLASS()
class PORTFOLIO_API ACPPBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPBuilding();

	//FUNCTIONS
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ChangeLevel(int Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	//VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)	
		UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* GhostMat;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* WoodMat;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* StoneMat;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* IronMat;
	UPROPERTY(EditAnywhere)
		FBuildStruct BuildStruct;
};
