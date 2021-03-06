// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when Actor Damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Return current health as a percentage of starting health (0..1)
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	virtual void BeginPlay() override;
	
	FTankDelegate OnTankDied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100;
};
