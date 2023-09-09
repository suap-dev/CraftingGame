// Fill out your copyright notice in the Description page of Project Settings.


#include "CNode.h"

#include "CEquipmentComponent.h"

// Sets default values
ACNode::ACNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ResourcesLeft = Capacity;

	InitialScale = MeshComp->GetComponentTransform().GetScale3D();
}

// this is called BEFORE BeginPlay, after the constructor.
void ACNode::PostInitializeComponents()
{
	// Remember to call the parent function!
	Super::PostInitializeComponents();

	TimeOfLastResourcesChange = GetWorld()->TimeSeconds;
}

// TODO: Add required reaction to interaction for CNode.
// The reaction that is required is providing the Instigator's InventoryComponent
// with adequate number of resources.
// Adequate to the strength of the tool and type of the resource?
void ACNode::OnInteract_Implementation(APawn* InstigatorPawn)
{
	FString DebugMessage =
		"\nSuccessful interaction (" + GetNameSafe(InstigatorPawn) + "->" + GetName() + ")";

	// Instigator's Equipment
	if (const UCEquipmentComponent* EquipmentComp =
		Cast<UCEquipmentComponent>(InstigatorPawn->GetComponentByClass<UCEquipmentComponent>()); ensure(EquipmentComp))
	{
		if (const FCItemTool Tool = EquipmentComp->Tool; MatchingTool() == Tool.Type)
		{
			DebugMessage += "\nTool OK.";

			if (ResourcesLeft > 0)
			{
				// if (UCInventoryComponent* InventoryComp =
				// 	Cast<UCInventoryComponent>(InstigatorPawn->GetComponentByClass<UCInventoryComponent>()))
				// {
				// 	// TMap<FCItemBase, uint32>* Contents = &InventoryComp->Contents;
				// 	// InventoryComp->Contents.Find();
				// }
			}
			else
			{
				DebugMessage += "\nNo resources left.";
			}
		}
		else
		{
			DebugMessage += "\nWrong Tool.";
		}
	}

	DrawDebugString(
		GetWorld(), FVector::Zero(),
		DebugMessage,
		this, FColor::White, /*Duration: */2.0f, /*bCastShadow: */true);
}

ECToolType ACNode::MatchingTool() const
{
	switch (ResourceType)
	{
	case ECResourceType::Stone:
		return ECToolType::Pickaxe;

	case ECResourceType::Wood:
		return ECToolType::Axe;

	default:
		return ECToolType::None;
	}
}

// Called when the game starts or when spawned
void ACNode::BeginPlay()
{
	Super::BeginPlay();
}

void ACNode::ResourcesChanged()
{
	TimeOfLastResourcesChange = GetWorld()->TimeSeconds;
}

double ACNode::TimeSinceLastResourcesChange() const
{
	return GetWorld()->TimeSeconds - TimeOfLastResourcesChange;
}

void ACNode::AdjustScale() const
{
	float ChangeablePart = 1.0f - MinimalScalingFactor;
	ChangeablePart = ChangeablePart * (ResourcesLeft / Capacity);
	const float ScalingFactor = MinimalScalingFactor + ChangeablePart;

	FVector NewScale = InitialScale;
	NewScale.X *= ScalingFactor;
	NewScale.Y *= ScalingFactor;

	MeshComp->SetWorldScale3D(NewScale);
}

// Called every frame
void ACNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ResourcesLeft < Capacity && TimeSinceLastResourcesChange() >= ReplenishTime)
	{
		ResourcesLeft++;
		ResourcesChanged();
		AdjustScale();
	}
}
