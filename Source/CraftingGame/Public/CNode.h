// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CInteractInterface.h"
#include "CEquipmentComponent.h"
#include "CNode.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	STONE,
	WOOD
};

UCLASS()
class CRAFTINGGAME_API ACNode : public AActor, public ICInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACNode();


	void PostInitializeComponents() override;

	void OnInteract_Implementation(APawn* InstigatorPawn) override;


	/** Indicate what tool is required for provided resource */
	UFUNCTION(BlueprintCallable)
	EToolType MatchingTool();


public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	/** Type of the provided resource */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (MultiLine = "true"))
	EResourceType ResourceType;

	/** How much resource can this node hold */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int32 Capacity;

	/**
	 * Current amount of the resource
	 * Filled to capacity during construction
	 * Replenishes 1 in ReplenishTime seconds
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	int32 ResourcesLeft;

	/** How many seconds it takes the node to regenerate 1 resource */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	double ReplenishTime;

	/** What's the RELATIVE scale of the node when all resources are depleted */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float MinimalScalingFactor;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResourcesChanged();

	double TimeSinceLastResourcesChange();

	void AdjustScale();

private:
	/** Holds the initial value of the scale for correct size adjustment */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	FVector InitialScale;

	/** Time of last resources change */
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	double TimeOfLastResourcesChange;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
