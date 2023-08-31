// Fill out your copyright notice in the Description page of Project Settings.


#include "CNode.h"

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
	check(GEngine);

	FString SelfName = GetName();
	FString InstigatorName = InstigatorPawn->GetName();

	FString Message = InstigatorName + " interacted with " + SelfName;

	GEngine->AddOnScreenDebugMessage(
		-1, 1.0f, FColor::Blue, Message);

	// Instigator's Equipment
	UCEquipmentComponent* InstigEquipment =
		InstigatorPawn->GetComponentByClass<UCEquipmentComponent>();

	if (InstigEquipment)
	{
		FCItemTool IntigTool = InstigEquipment->Tool;
		if (MatchingTool() == IntigTool.Type)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 1.0f, FColor::Blue, "Tool OK.");
			if (ResourcesLeft > 0)
			{
				UCInventoryComponent* InstigInventory =
					InstigatorPawn->GetComponentByClass<UCInventoryComponent>();

				if (InstigInventory)
				{
// 					TMap<FCItemBase, uint32>* Contents = &InstigInventory->Contents;
// 					InstigInventory->Contents.Find()
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(
					-1, 1.0f, FColor::Purple, "But no resources left.");
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 1.0f, FColor::Purple, "Wrong Tool");
		}
	}
}

ECToolType ACNode::MatchingTool()
{
	switch (ResourceType)
	{
	case ECResourceType::STONE:
		return ECToolType::PICKAXE;
		break;
	case ECResourceType::WOOD:
		return ECToolType::AXE;
		break;
	default:
		return ECToolType::NONE;
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

double ACNode::TimeSinceLastResourcesChange()
{
	return GetWorld()->TimeSeconds - TimeOfLastResourcesChange;
}

void ACNode::AdjustScale()
{
	float ChangablePart = 1.0f - MinimalScalingFactor;
	ChangablePart = ChangablePart * (ResourcesLeft / Capacity);
	float ScalingFactor = MinimalScalingFactor + ChangablePart;

	FVector NewScale = InitialScale;
	NewScale.X *= ScalingFactor;
	NewScale.Y *= ScalingFactor;

	MeshComp->SetWorldScale3D(NewScale);
}

// Called every frame
void ACNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ResourcesLeft < Capacity && TimeSinceLastResourcesChange() >= ReplenishTime) {
		ResourcesLeft++;
		ResourcesChanged();
		AdjustScale();
	}

}

