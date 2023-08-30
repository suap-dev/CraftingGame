// Fill out your copyright notice in the Description page of Project Settings.


#include "CDefaultCharacter.h"

#include "CInteractComponent.h"
#include "CEquipmentComponent.h"
#include "CInventoryComponent.h"

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
// 	FMath::Clamp(1.0, 2.0, 3.0);

}

// Called to bind functionality to input
void ACDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACDefaultCharacter::MoveForward(float ScaleValue)
{
	AddMovementInput(GetActorForwardVector(), ScaleValue);
}

void ACDefaultCharacter::MoveRight(float ScaleValue)
{
	AddMovementInput(GetActorRightVector(), ScaleValue);
}
