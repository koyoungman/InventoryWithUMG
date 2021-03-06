// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Interface/Action.h"
#include "InventoryWithUMGCharacter.h"
#include "InventorySlot.h"

UGameHUD::UGameHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivateInventory = true;
	InventoryVisible = ESlateVisibility::Hidden;
	ActopnMenuVisible = ESlateVisibility::Hidden;
	ActionText = FText::FromString(TEXT(""));
}

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryMenu = Cast<UVerticalBox>(GetWidgetFromName("InventoryMenu"));
	ActionMenu = Cast<UVerticalBox>(GetWidgetFromName("ActionMenu"));
	CancelButton = Cast<UButton>(GetWidgetFromName("CancelButton"));
	DropButton = Cast<UButton>(GetWidgetFromName("DropButton"));
	UseButton = Cast<UButton>(GetWidgetFromName("UseButton"));

	CancelButton->OnClicked.AddDynamic(this, &UGameHUD::OnCancelButtonClicked);
	DropButton->OnClicked.AddDynamic(this, &UGameHUD::OnDropButtonClicked);
	UseButton->OnClicked.AddDynamic(this, &UGameHUD::OnUseButtonClicked);
	
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

TArray<FInventory>& UGameHUD::GetInventory()
{
	return Inventory;
}

UWidgetAnimation * UGameHUD::GetMenuAnim_Implementation() const
{
	return nullptr;
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

void UGameHUD::ActionComplete()
{
	ActivateInventory = true;
	ActopnMenuVisible = ESlateVisibility::Hidden;
}

/**
 * Cancel Button Was Clicked.
 */
void UGameHUD::OnCancelButtonClicked()
{
	ActionComplete();
}

/**
* Drop Button Was Clicked.
*/
void UGameHUD::OnDropButtonClicked()
{
	// Interface Message Call.
	if (CharacterReference->GetClass()->ImplementsInterface(UAction::StaticClass()))
	{
		IAction::Execute_DropAction(CharacterReference, Inventory[InventorySlotClicked].Item);
		Inventory.RemoveAt(InventorySlotClicked);
		RefeshInventory();
		ActionComplete();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterReference->GetClass()->ImplementsInterface(UAction::StaticClass()) == false"));
	}
}

/**
* Use Button Was Clicked.
*/
void UGameHUD::OnUseButtonClicked()
{
	// Interface Message Call.
	if (Inventory[InventorySlotClicked].Item->GetClass()->ImplementsInterface(UAction::StaticClass()))
	{
		IAction::Execute_UseAction(Inventory[InventorySlotClicked].Item);
		Inventory.RemoveAt(InventorySlotClicked);
		RefeshInventory();
		ActionComplete();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterReference->GetClass()->ImplementsInterface(UAction::StaticClass()) == false"));
	}
}

/**
* Inventory Button Was Clicked.
*/
void UGameHUD::OnSlotButtonWasClicked(int SlotClicked)
{
	ActivateInventory = false;

	InventorySlotClicked = SlotClicked;

	ActionText = Inventory[SlotClicked].ActionText;

	ActopnMenuVisible = ESlateVisibility::Visible;
	
}
