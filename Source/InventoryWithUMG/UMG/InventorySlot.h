// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * BP_InventorySlot 블루프린트에 부모로 설정해 주세요.
 */
UCLASS()
class INVENTORYWITHUMG_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	class UImage* Image;

private:
	// 함수바인딩을 위해 Pure함수로 작성.
	UFUNCTION(BlueprintPure, Category="Bind", Meta = (AllowPrivateAccess = true))
	struct FSlateBrush GetInventoryImage();
};
