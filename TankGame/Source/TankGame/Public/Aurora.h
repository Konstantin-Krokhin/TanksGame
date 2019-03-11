// Copyright Konstantin Krokhin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Aurora.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuroraDelegate);

UCLASS()
class TANKGAME_API AAurora : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAurora();

	FAuroraDelegate AuroraDied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 AuroraCurrentHealth;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by the engine when Actor Damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SwordDamage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 20;

};
