// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "Components/Image.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Image = Cast<UImage>(GetWidgetFromName("Image_0"));
}

FSlateBrush UInventorySlot::GetInventoryImage()
{
	auto s = FSlateBrush();
	return s;
}
