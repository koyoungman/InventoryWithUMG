// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "Components/VerticalBox.h"
#include "InventoryWithUMGCharacter.h"
#include "InventorySlot.h"

UGameHUD::UGameHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivateInventory = true;
	InventoryVisible = ESlateVisibility::Hidden;
	ActopnMenuVisible = ESlateVisibility::Hidden;
	ActionText = TEXT("");
}

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryMenu = Cast<UVerticalBox>(GetWidgetFromName("InventoryMenu"));
	ActionMenu = Cast<UVerticalBox>(GetWidgetFromName("ActionMenu"));
	
	Slots.Add(Cast<UInventorySlot>(GetWidgetFromName("Slot_0")));
	Slots.Add(Cast<UInventorySlot>(GetWidgetFromName("Slot_1")));
	Slots.Add(Cast<UInventorySlot>(GetWidgetFromName("Slot_2")));
	Slots.Add(Cast<UInventorySlot>(GetWidgetFromName("Slot_3")));
	Slots.Add(Cast<UInventorySlot>(GetWidgetFromName("Slot_4")));

	for (auto Slot : Slots)
	{
		Slot->ButtonWasClicked.AddUObject(this, &UGameHUD::OnSlotButtonWasClicked);
	}

	CharacterReference = Cast<AInventoryWithUMGCharacter>(GetOwningPlayer()->GetCharacter());
}

UVerticalBox* UGameHUD::GetInventoryMenu() const
{
	return InventoryMenu;
}

void UGameHUD::RefeshInventory()
{
	ActivateInventory = true;

	for(int32 i = 0; i< Slots.Num(); i++)
	{
		if (i < Inventory.Num())
		{
			Slots[i]->SetPickupImage(Inventory[i].ItemImage);
		}
		else
		{
			Slots[i]->SetPickupImage(nullptr);
		}
	}
}

void UGameHUD::OnSlotButtonWasClicked(int SlotIndex)
{

}
