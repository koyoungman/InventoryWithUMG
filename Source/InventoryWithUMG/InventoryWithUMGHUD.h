// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryWithUMGHUD.generated.h"

UCLASS()
class AInventoryWithUMGHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInventoryWithUMGHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My HUD")
	bool ShowCrosshairs;
};

