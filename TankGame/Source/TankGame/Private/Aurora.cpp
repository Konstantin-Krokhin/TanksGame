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

/*
void AAurora::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Entered OnHit Event !!!"));
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		UE_LOG(LogTemp, Warning, TEXT("Entered if !!!!!!!!!!!!!!!!!!!!!!!!!"));
		UGameplayStatics::ApplyRadialDamage(
			this,
			SwordDamage,
			GetActorLocation(),
			100.f,
			UDamageType::StaticClass(),
			TArray<AActor*>() // damage all actors
		);
	}
}*/

// Called by the engine when Actor Damage is dealt
float AAurora::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
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

