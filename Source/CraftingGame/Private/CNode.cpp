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

void ACNode::OnInteract_Implementation(APawn* InstigatorPawn)
{
	check(GEngine);

	FString SelfName = GetName();
	FString InstigatorName = InstigatorPawn->GetName();

	FString Message = InstigatorName + " interacted with " + SelfName;

	GEngine->AddOnScreenDebugMessage(
		-1, 2.0f, FColor::Yellow, Message);
}

EToolType ACNode::MatchingTool()
{
	switch (ResourceType)
	{
	case EResourceType::STONE:
		return EToolType::PICKAXE;
		break;
	case EResourceType::WOOD:
		return EToolType::AXE;
		break;
	default:
		return EToolType::NONE;
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

