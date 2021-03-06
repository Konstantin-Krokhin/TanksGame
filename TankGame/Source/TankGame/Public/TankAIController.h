// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close AI Tank get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 10000;

private:
	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

};
