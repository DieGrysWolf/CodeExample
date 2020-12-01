// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPPGameInstance.generated.h"

//this was used for the widgets originally
//decided to switch to a blueprint solution for greater robustness

UCLASS()
class PORTFOLIO_API UCPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCPPGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
};
