// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerControllerBase.h"

void ACPP_PlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}
