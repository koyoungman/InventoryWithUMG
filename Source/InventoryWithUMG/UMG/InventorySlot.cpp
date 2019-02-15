// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Image = Cast<UImage>(GetWidgetFromName("Image_0"));
	Button = Cast<UButton>(GetWidgetFromName("Button_0"));
	if (nullptr != Button)
	{
		// 버튼 클릭 이벤트 추가.
		Button->OnClicked.AddDynamic(this, &UInventorySlot::OnButtonClicked);
	}
}

FSlateBrush UInventorySlot::GetInventoryImage()
{
	Brush.SetResourceObject(PickupImage);
	return Brush;
}

bool UInventorySlot::InventoryCheck()
{
	return (nullptr != PickupImage);
}

void UInventorySlot::OnButtonClicked()
{
	// Inventory Slot Was Clicked
	ButtonWasClicked.Broadcast(InventorySlot);
}
