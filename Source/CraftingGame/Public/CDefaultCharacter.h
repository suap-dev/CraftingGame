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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCInteractComponent> InteractComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCEquipmentComponent> EquipmentComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCInventoryComponent> InventoryComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Default")
	float MinCameraPitch = -50.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Default")
	float MaxCameraPitch = 10.0f;


	// DONT: Implement input actions, let's do this part in Blueprint for now
	// 
	// Implement movement and rotation functions that we can later connect with Enhanced Input:	
	// TODO: some way of choosing a tool from Inventory and putting it in Equipment
	// 
	// TODO: remove redundant methods and connect behavior with Enhanced Input

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Default")
	void MoveForward(float ScaleValue);

	UFUNCTION(BlueprintCallable, Category = "Default")
	void MoveRight(float ScaleValue);

	UFUNCTION(BlueprintCallable, Category = "Default")
	void LookUp(float Value) const; // not sure if this one is actually necessary

	UFUNCTION(BlueprintCallable, Category = "Default")
	void LookRight(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
