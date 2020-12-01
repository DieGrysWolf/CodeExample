// Fill out your copyright notice in the Description page of Project Settings.

//THIS IS NOT USED (created a local one)

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstance.h"
#include "CPPBuildStruct.generated.h"

USTRUCT()
struct FCPPBuildStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* BaseMaterial = nullptr;

};
