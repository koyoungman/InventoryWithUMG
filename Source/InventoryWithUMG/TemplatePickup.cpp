// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplatePickup.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UMG/PickupText.h"
#include "InventoryWithUMGCharacter.h"
#include "UMG/GameHUD.h"

// Sets default values
ATemplatePickup::ATemplatePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeScale3D(FVector(8.0f, 8.0f, 8.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATemplatePickup::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ATemplatePickup::OnEndOverlap);
	Trigger->SetCollisionProfileName(TEXT("Custom"));
	// Projectile Collision Ignore.
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	if (StaticMeshFinder.Succeeded())
	{
		StaticMesh->SetStaticMesh(StaticMeshFinder.Object);
		CustomStaticMesh = StaticMeshFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> ItemImageFinder(TEXT("Texture2D'/Game/Textures/Can.Can'"));
	if (ItemImageFinder.Succeeded())
	{
		CustomImage = ItemInfo.ItemImage = ItemImageFinder.Object;
	}
	CustomPickupText = ItemInfo.PickupText = FText::FromString(TEXT("Canned Beans"));
	CustomActionText = ItemInfo.ActionText = FText::FromString(TEXT("Eat Beans"));

	AddHealth = 0.25f;
	AddEnergy = 0.25f;
	AddMood = 0.25f;

	// PickupText 블루프린트 클래스 레퍼런스 설정
	// 경로 끝에 _C 추가.
	static ConstructorHelpers::FClassFinder<UPickupText> PickupTextClassFinder(TEXT("WidgetBlueprint'/Game/UMG/BP_PickupText.BP_PickupText_C'"));
	if (PickupTextClassFinder.Succeeded())
	{
		PickupTextClass = PickupTextClassFinder.Class;
	}
}

/**
* BP Construction Script
*/
void ATemplatePickup::OnConstruction(const FTransform & Transform)
{
	ItemInfo.Item = this;
	ItemInfo.ItemImage = CustomImage;
	ItemInfo.PickupText = CustomPickupText;
	ItemInfo.ActionText = CustomActionText;

	StaticMesh->SetStaticMesh(CustomStaticMesh);
}

// Called when the game starts or when spawned
void ATemplatePickup::BeginPlay()
{
	Super::BeginPlay();

	// PickupText Widget 생성.
	PickupTextReference = CreateWidget<UPickupText>(GetWorld(), PickupTextClass);

	// Set members in inventoryStruct.
	ItemInfo.Item = this;

	PickupTextReference->PickupActor = TWeakObjectPtr<AActor>(ItemInfo.Item);
	PickupTextReference->PickupText = ItemInfo.PickupText;

	// GetPlayerChatacter(PlayerIndex : 0)
	ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();

	// Cast To FirstPersonCharacter
	AInventoryWithUMGCharacter* FirstPersonCharacter = Cast<AInventoryWithUMGCharacter>(PlayerCharacter);
	if (nullptr == FirstPersonCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast<AInventoryWithUMGCharacter>(PlayerCharacter) == nullptr"));
		return;
	}
		
	CharacterReference = FirstPersonCharacter;

	CharacterReference->OnPickupItem.AddUObject(this, &ATemplatePickup::OnPickupItem);

}

// Called every frame
void ATemplatePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Overlap Trigger Script
// Overlap Trigger Script
void ATemplatePickup::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AInventoryWithUMGCharacter* FirstPersonCharacter = Cast<AInventoryWithUMGCharacter>(OtherActor);
	if (nullptr == FirstPersonCharacter)
		return;

	PickupTextReference->AddToViewport();

	IsInRange = true;
}

void ATemplatePickup::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AInventoryWithUMGCharacter* FirstPersonCharacter = Cast<AInventoryWithUMGCharacter>(OtherActor);
	if (nullptr == FirstPersonCharacter)
		return;

	PickupTextReference->RemoveFromParent();

	IsInRange = false;
}
#pragma endregion

const FInventory & ATemplatePickup::GetItemInfo() const
{
	return ItemInfo;
}

/**
* Pickup and add items to the inventory then refresh it.
*/
void ATemplatePickup::OnPickupItem()
{
	if (GetActorEnableCollision() && IsInRange)
	{
		UGameHUD* GameHUDReference = CharacterReference->GetGameHUDReference();
		GameHUDReference->GetInventory().Add(ItemInfo);
		PickupTextReference->RemoveFromParent();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		GameHUDReference->RefeshInventory();
	}
}

void ATemplatePickup::UseAction_Implementation()
{
	CharacterReference->HealthValue += AddHealth;
	CharacterReference->EnergyValue += AddEnergy;
	CharacterReference->MoodValue += AddMood;

	Destroy();
}

