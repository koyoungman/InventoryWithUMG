// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class AActor* Item = nullptr;

	UPROPERTY(EditAnywhere)
	class UTexture2D* ItemImage = nullptr;

	UPROPERTY(EditAnywhere)
	FText PickupText;

	UPROPERTY(EditAnywhere)
	FText ActionText;
};
