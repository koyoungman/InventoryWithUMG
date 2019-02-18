// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Inventory.h"
#include "GameHUD.generated.h"

/**
 * BP_GameHUD 블루프린트에 부모로 설정해 주세요.
 */
UCLASS()
class INVENTORYWITHUMG_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameHUD(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	class UVerticalBox* InventoryMenu;
	class UVerticalBox* ActionMenu;
	class UButton* CancelButton;
	class UButton* DropButton;
	class UButton* UseButton;

	TArray<class UInventorySlot*> Slots;

	int32 InventorySlotClicked;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	class AInventoryWithUMGCharacter* CharacterReference;

#pragma region getter / settger
public:
	UFUNCTION(BlueprintPure)
	class UVerticalBox* GetInventoryMenu() const;

	UFUNCTION(BlueprintPure)
	TArray<FInventory>& GetInventory();
#pragma endregion

private:
	TArray<FInventory> Inventory;

public:
	/**
	* 프로퍼티 바인딩을 위한 UPROPERTY 선언.
	*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool ActivateInventory;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	ESlateVisibility InventoryVisible;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	ESlateVisibility ActopnMenuVisible;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FText ActionText;

public:
	void RefeshInventory();

private:
	void ActionComplete();


private:
	UFUNCTION(Meta = (AllowPrivateAccess = true))
	void OnCancelButtonClicked();

	UFUNCTION(Meta = (AllowPrivateAccess = true))
	void OnDropButtonClicked();

	UFUNCTION(Meta = (AllowPrivateAccess = true))
	void OnUseButtonClicked();

	UFUNCTION(Meta = (AllowPrivateAccess = true))
	void OnSlotButtonWasClicked(int SlotIndex);

};
