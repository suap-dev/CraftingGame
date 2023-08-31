// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Chaos/Map.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};


UENUM(BlueprintType)
enum class ECToolType : uint8
{
	NONE,
	PICKAXE,
	AXE,

};

UENUM(BlueprintType)
enum class ECResourceType : uint8
{
	STONE,
	WOOD
};


USTRUCT(BlueprintType)
struct FCItemBase
{

	GENERATED_BODY()

	// TODO: fix UPROPERTY'ies
	// Should it be Read/Write? I don't want to change the item's name
	// after it's been created. Or do I?
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString	Name;

	// TODO: ensure this is unique
	uint16 ID;

	// TODO: create hashing function for items. Maybe by ID, or ID and Name?

};


USTRUCT(BlueprintType)
struct FCItemTool : public FCItemBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECToolType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 Power;

};


USTRUCT(BlueprintType)
struct FCItemResource
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECResourceType Type;

};