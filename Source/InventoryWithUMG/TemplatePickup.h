// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/Inventory.h"
#include "Interface/Action.h"
#include "TemplatePickup.generated.h"

UCLASS()
class INVENTORYWITHUMG_API ATemplatePickup : public AActor, public IAction
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UMG, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UPickupText> PickupTextClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	class UPickupText* PickupTextReference;

public:	
	// Sets default values for this actor's properties
	ATemplatePickup();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	bool IsInRange;
	TWeakObjectPtr<class AInventoryWithUMGCharacter> CharacterReference;

protected:
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AddHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AddEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AddMood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FInventory ItemInfo;

public:
	UFUNCTION(BlueprintPure)
	const FInventory& GetItemInfo() const;

private:
	void OnPickupItem();

#pragma region IAction
public:
	/*
	* IAction Interface.
	*/
	void UseAction_Implementation() override;
#pragma endregion
};
