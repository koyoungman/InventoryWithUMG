// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupText.h"
#include "Engine/Classes/GameFramework/Actor.h"

void UPickupText::NativeConstruct()
{
	Super::NativeConstruct();
}

// 별로 좋지 않은 방법. 일단은 강좌 대로 함.
void UPickupText::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PickupActor.IsValid() == false)
		return;
	
	const FVector& WorldLocation = PickupActor->GetActorLocation();
	FVector2D ScreenLocation;
	
	// Blueprint : GetPlayerController(PlayerIndex : 0)
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// Blueprint : ConvertWorldLocationToScreenLocation
	bool Select = PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

	// Blueprint : Select
	ESlateVisibility Visibility = (Select) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	SetVisibility(Visibility);
	SetPositionInViewport(ScreenLocation);
}
