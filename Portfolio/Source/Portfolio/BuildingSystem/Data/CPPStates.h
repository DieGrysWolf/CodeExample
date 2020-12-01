// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPStates.generated.h"

//enumeration to keep track of player's states
//created enum to add states easier

UENUM()
enum ECPPStates
{
	STATE_Passive	UMETA(DisplayName = "Passive"),
	STATE_Build		UMETA(DisplayName = "Build")
};
