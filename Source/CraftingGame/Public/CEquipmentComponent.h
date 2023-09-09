// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CInventoryComponent.h"
#include "Components/ActorComponent.h"
#include "CEquipmentComponent.generated.h"


// TODO: EquipmentComponent and InventoryComponent should be merged into one
// maybe with Equipment(all available slots) + Backpack(as a slot) which is a map?
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRAFTINGGAME_API UCEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCEquipmentComponent();

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	FCItemTool Tool;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
