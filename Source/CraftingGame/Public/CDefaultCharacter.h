// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CDefaultCharacter.generated.h"

class UCInteractComponent;
class UCEquipmentComponent;
class UCInventoryComponent;

UCLASS()
class CRAFTINGGAME_API ACDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACDefaultCharacter();
		
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UCInteractComponent> InteractComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UCEquipmentComponent> EquipmentComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UCInventoryComponent> InventoryComp;

	// DONT: Implement input actions, let's do this part in Blueprint for now
	// 
	// Implement movement and rotation functions that we can later connect with Enhanced Input:
	// TODO: void MoveForward(float ScaleValue);
	// TODO: void MoveRight(float ScaleValue);
	// TODO: void LookUp(float Value); // not sure if this one is actualy necesary
	// TODO: void LookRight(float Value);
	// TODO: void Interact(AActor* Parent); // this should use the InteractComponent's Interact method
	// TODO: some way of choosing a tool from Inventory and putting it in Equipment
	// 
	// TODO: remove redundant methods and connect behavior with Enhanced Input

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
