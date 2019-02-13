// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "InventoryWithUMGCharacter.h"

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterReference = Cast<AInventoryWithUMGCharacter>(GetOwningPlayer()->GetCharacter());
}