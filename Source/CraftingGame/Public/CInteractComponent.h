// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRAFTINGGAME_API UCInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCInteractComponent();

	/** Scans for objects to interact, if they implement InteractInterface then do stuff */
	UFUNCTION(BlueprintCallable)
	void Interact() const;
};
