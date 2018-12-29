// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Engine/World.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for blueprint BeginPlay() to work!
	CurrentHealth = StartingHealth;

}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Died"));
		OnDeath.Broadcast();
	}
	return DamageToApply;

}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

