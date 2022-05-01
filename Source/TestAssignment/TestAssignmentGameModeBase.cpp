// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestAssignmentGameModeBase.h"
#include "TAPlayer.h"
#include "TAPlayerHUD.h"

ATestAssignmentGameModeBase::ATestAssignmentGameModeBase()
{
	DefaultPawnClass = ATAPlayer::StaticClass();
	HUDClass = ATAPlayerHUD::StaticClass();
}
