// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "InventoryWithUMGGameMode.h"
#include "InventoryWithUMGHUD.h"
#include "InventoryWithUMGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryWithUMGGameMode::AInventoryWithUMGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AInventoryWithUMGHUD::StaticClass();
}
