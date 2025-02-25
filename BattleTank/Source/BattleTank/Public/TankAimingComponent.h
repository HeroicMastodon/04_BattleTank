// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {Reloading, Aiming, Locked, NoAmmo};
// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Hold Barrel's perperties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BluePrintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringState GetFiringState() const;

	UFUNCTION(BluePrintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 RoundsLeft = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	bool IsBarrelMoving();

	virtual void BeginPlay() override;

private:	

	UTankBarrel* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	UTankTurret* Turret = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	FVector AimDirection;

	

};
