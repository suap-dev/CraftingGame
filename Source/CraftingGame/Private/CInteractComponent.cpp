// Fill out your copyright notice in the Description page of Project Settings.


#include "CInteractComponent.h"
#include "CInteractInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Private/KismetTraceUtils.h"

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
		bool bHit = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			Start, End,
			ObjectQueryParams, QueryParams);

		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			DrawDebugString(
				GetWorld(), FVector::Zero(),
				FString::Printf(
					TEXT("%s attempting interaction with %s"),
					*Owner->GetName(), *HitActor->GetName()),
				HitActor, FColor::Cyan, /*Duration: */2.0f, /*bCastShadow: */true);
		}

		if (HitActor && HitActor->Implements<UCInteractInterface>())
		{
			ICInteractInterface::Execute_OnInteract(HitActor, Cast<APawn>(Owner));

		}

		DrawDebugLineTraceSingle(
			GetWorld(), Start, End,
			EDrawDebugTrace::ForDuration, bHit, HitResult,
			FColor::Blue, FColor::Green, 2.0f);

	}

}
