// Fill out your copyright notice in the Description page of Project Settings.


#include "CDefaultCharacter.h"

#include "CInteractComponent.h"
#include "CEquipmentComponent.h"
#include "CInventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACDefaultCharacter::ACDefaultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractComp = CreateDefaultSubobject<UCInteractComponent>("InteractComp");
	EquipmentComp = CreateDefaultSubobject<UCEquipmentComponent>("EquipmentComp");
	InventoryComp = CreateDefaultSubobject<UCInventoryComponent>("InventoryComp");
}

// Called when the game starts or when spawned
void ACDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACDefaultCharacter::MoveForward(const float ScaleValue)
{
	AddMovementInput(GetActorForwardVector(), ScaleValue);
}

void ACDefaultCharacter::MoveRight(const float ScaleValue)
{
	AddMovementInput(GetActorRightVector(), ScaleValue);
}

void ACDefaultCharacter::LookUp(const float Value) const
{
	if (USpringArmComponent* SpringArm = GetComponentByClass<USpringArmComponent>(); ensure(SpringArm))
	{
		FRotator Rotation = SpringArm->GetRelativeRotation();
		Rotation.Pitch =
			FMath::Clamp(Rotation.Pitch + Value, MinCameraPitch, MaxCameraPitch);

		SpringArm->SetRelativeRotation(Rotation);
	}
}

void ACDefaultCharacter::LookRight(const float Value)
{
	AddControllerYawInput(Value);
}
