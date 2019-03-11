// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Aurora.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GetPawn()) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		//auto PossessedTank = Cast<ATank>(InPawn);
		//if (!PossessedTank) { return; }

		PawnTank = Cast<ATank>(InPawn);
		if (!PawnTank) { return; }
		
		// Subscribe OnPossessedTankDeath method to the Tank's death event
		PawnTank->OnTankDied.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	//auto PossessedTank = Cast<ATank>(PawnTank);
	if (!PawnTank) { return; }
	PawnTank->OnTankDied.RemoveDynamic(this, &ATankPlayerController::OnPossessedTankDeath);

	//DetachFromControllerPendingDestroy()

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UClass* Character = LoadObject<UClass>(this, *FString("Blueprint'/Game/ParagonAurora/Aurora_BP.Aurora_BP_C'"));

	auto TankLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	TankLocation.Z = 300.f;

	Aurora = GetWorld()->SpawnActor<AAurora>(Character, TankLocation, FRotator::ZeroRotator, ActorSpawnParams);

	if (!Aurora) { return; }
	// Subscribe OnPossessedAuroraDeath method to the Aurora's death event
	Aurora->AuroraDied.AddUniqueDynamic(this, &ATankPlayerController::OnAuroraDeath);
}

void ATankPlayerController::OnAuroraDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // if not possesing
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent) { return; }

	FVector OutHitLocation; // Out parameter

	if (GetSightRayHitLocation(OutHitLocation)) //It is going to line trace
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection and see what we hit
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}