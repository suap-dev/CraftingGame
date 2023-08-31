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


void UCInteractComponent::Interact()
{
	AActor* Owner = GetOwner();

	// Should I first check if Owner is a Character class, preferably defined by me?
	UCameraComponent* Camera = GetOwner()->GetComponentByClass<UCameraComponent>();

	if (Camera)
	{
		FVector Start = Camera->GetComponentLocation();
		FVector End = Start + Camera->GetForwardVector() * 1000;
		
		
		FCollisionObjectQueryParams ObjectQueryParams;
// 		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Owner);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			Start, End,
			ObjectQueryParams, QueryParams);

		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			check(GEngine);
			GEngine->AddOnScreenDebugMessage(
				-1, 1.0f, FColor::Blue,
				Owner->GetName() + " have hit " + HitActor->GetName());

		}

		if (HitActor && HitActor->Implements<UCInteractInterface>())
		{
			ICInteractInterface::Execute_OnInteract(HitActor, Cast<APawn>(Owner));

		}

		DrawDebugLine(
			GetWorld(), Start, End,
			FColor::Blue,
			false, 2.0f, 0, 1.5f);

	}

}
