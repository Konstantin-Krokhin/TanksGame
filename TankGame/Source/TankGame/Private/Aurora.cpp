// Copyright Konstantin Krokhin


#include "Aurora.h"

// Sets default values
AAurora::AAurora()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAurora::BeginPlay()
{
	Super::BeginPlay();
	AuroraCurrentHealth = StartingHealth;
}

// Called by the engine when Actor Damage is dealt
float AAurora::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, 
	class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, AuroraCurrentHealth);

	AuroraCurrentHealth -= DamageToApply;
	if (AuroraCurrentHealth <= 0)
	{
		AuroraDied.Broadcast();
	}

	return DamageToApply;
}

// Called to bind functionality to input
void AAurora::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

