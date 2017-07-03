// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MoreItems.h"
#include "MoreItemsGameMode.h"
#include "MoreItemsHUD.h"
#include "MoreItemsCharacter.h"

AMoreItemsGameMode::AMoreItemsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMoreItemsHUD::StaticClass();
}
