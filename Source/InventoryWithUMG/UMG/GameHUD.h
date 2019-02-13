// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * GameHUD 블루프린트에 부모로 설정해 주세요.
 */
UCLASS()
class INVENTORYWITHUMG_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	class AInventoryWithUMGCharacter* CharacterReference;
};
