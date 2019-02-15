// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

public:
	FInventory()
	{
		Item = nullptr;
		ItemImage = nullptr;
	}

public:
	UPROPERTY(EditAnywhere)
	AActor* Item;

	UPROPERTY(EditAnywhere)
	class UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	FText PickupText;

	UPROPERTY(EditAnywhere)
	FText ActionText;
};
