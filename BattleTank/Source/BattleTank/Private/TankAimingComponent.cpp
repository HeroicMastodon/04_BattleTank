// Fill out your copyright notice in the Description page of Project Settin
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "Public/TankTurret.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) 
	{ FiringState = EFiringState::Reloading; }

	else if (IsBarrelMoving())
	{ FiringState = EFiringState::Aiming; }
	
	else 
	{ FiringState = EFiringState::Locked; }
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay(); // Needed for blueprint BeginPlay() to work!
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}



void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//FVector AimDirection;
	DrawDebugLine(GetWorld(), StartLocation, HitLocation, FColor::Red, false, -1.f, 0, 20.f);
	// Calculate the OutLaunchVelocity
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		
	}
	
}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	///Wordk-out diffference between current barrel totation, and aimdirection
	if (!ensure(Barrel && Turret)) { return; };
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimASRotator: %s"), *AimAsRotator.ToString())

	Barrel->Elevate(DeltaRotator.Pitch); 
	if (DeltaRotator.Yaw > 180) { DeltaRotator.Yaw = -DeltaRotator.Yaw; }
	Turret->Rotate(DeltaRotator.Yaw);
}



void UTankAimingComponent::Fire()
{
	

	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// Spawn a projectile at socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

