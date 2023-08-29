// Fill out your copyright notice in the Description page of Project Settings.


#include "CInteractComponent.h"
#include "CInteractInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UCInteractComponent::UCInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCInteractComponent::Interact(AActor* Parent)
{
	// Should I first check if Parent is a Character class, preferably defined by me?
	
	UCameraComponent* Camera = Parent->GetComponentByClass<UCameraComponent>();

	if (Camera)
	{
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + Camera->GetComponentRotation().Vector() * 1000;

		FHitResult HitResult;
		FCollisionObjectQueryParams QueryParams;
		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, QueryParams);

		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->Implements<UCInteractInterface>())
		{
			ICInteractInterface::Execute_OnInteract(HitActor, Cast<APawn>(GetOwner()));
		}

		DrawDebugLine(
			GetWorld(), Start, End,
			FColor::Blue,
			false, 2.0f, 0, 1.5f);
	}
}
