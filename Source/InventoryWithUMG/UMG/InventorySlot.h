// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

// 이벤트 디스패처 데이터형 선언.
DECLARE_MULTICAST_DELEGATE_OneParam(FButtonWasClicked, int32)

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
	class UButton* Button;

	class UTexture2D* PickupImage;
	struct FSlateBrush Brush;

public:
	// UMG 블루프린트에서 값을 셋팅해 주기위한 UPROPERTY 선언.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventorySlot;

public:
	void SetPickupImage(UTexture2D* Image);

private:
	// 함수바인딩을 위해 Pure함수로 작성.
	UFUNCTION(BlueprintPure, Category="Bind", Meta = (AllowPrivateAccess = true))
	struct FSlateBrush GetInventoryImage();

	UFUNCTION(BlueprintPure, Category = "Bind", Meta = (AllowPrivateAccess = true))
	bool InventoryCheck();

private:
	UFUNCTION()
	void OnButtonClicked();

public:
	// 이벤트 디스패처
	FButtonWasClicked ButtonWasClicked;

};
