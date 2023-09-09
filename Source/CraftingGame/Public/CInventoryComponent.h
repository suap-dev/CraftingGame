// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

// TODO: EquipmentComponent and InventoryComponent should be merged into one
// maybe with Equipment(all available slots) + Backpack(as a slot) which is a map?
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRAFTINGGAME_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCInventoryComponent();

	// 	TMap<FCItemTool, uint32> Contents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};


UENUM(BlueprintType)
enum class ECToolType : uint8
{
	None,
	Pickaxe,
	Axe,
};

UENUM(BlueprintType)
enum class ECResourceType : uint8
{
	Stone,
	Wood
};


USTRUCT(BlueprintType)
struct FCItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	// TODO: ensure this is unique
	uint16 ID;

	// TODO: create hashing function for items. Maybe by ID, or ID and Name?
};


USTRUCT(BlueprintType)
struct FCItemTool : public FCItemBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECToolType Type = ECToolType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 Power = 1;
};


USTRUCT(BlueprintType)
struct FCItemResource
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECResourceType Type;
};
