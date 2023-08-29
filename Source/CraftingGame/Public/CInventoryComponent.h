// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CInventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRAFTINGGAME_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCInventoryComponent();
	
// 	TMap<FCItemBase, uint32> Contents;

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
struct FCItemBase {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;

};


USTRUCT(BlueprintType)
struct FCItemTool
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