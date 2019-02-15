// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "Components/VerticalBox.h"
#include "InventoryWithUMGCharacter.h"

UGameHUD::UGameHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivateInventory = true;
	InventoryVisible = ESlateVisibility::Hidden;
}

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryMenu = Cast<UVerticalBox>(GetWidgetFromName("InventoryMenu"));

	CharacterReference = Cast<AInventoryWithUMGCharacter>(GetOwningPlayer()->GetCharacter());
}

UVerticalBox* UGameHUD::GetInventoryMenu() const
{
	return InventoryMenu;
}
