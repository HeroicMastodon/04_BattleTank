// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Public/TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
};


 void ATankPlayerController::AimTowardsCrosshair()
 {
	 if (!GetPawn()) { return; }
	 auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	 if (!ensure(AimingComponent)) { return; }
	 
	 FVector HitLocation;  // Out parameter
	 bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	 if (bGotHitLocation)
	 {
		AimingComponent->AimAt(HitLocation);
	 }
 }

 // Get world location of linetrace through crosshair, true if hits landscape
 bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
 {
	// Find the crosshair position
	 int32 ViewportSizeX, ViewportSizeY;
	 GetViewportSize(ViewportSizeX, ViewportSizeY);
	 auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	 FVector LookDirection;
	 if (GetLookDirection(ScreenLocation, LookDirection))
	 {
		 // Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	 }

	 return false;
 }

 bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
 {
	 FVector CameraWorldLocation;
	 DeprojectScreenPositionToWorld(
		 ScreenLocation.X, 
		 ScreenLocation.Y, 
		 CameraWorldLocation, 
		 LookDirection);
	 

		 return true;
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
 {
	 FHitResult HitResult;
	 auto StartLocation = PlayerCameraManager->GetCameraLocation();
	 auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	 if (GetWorld()->LineTraceSingleByChannel(
		 HitResult,
		 StartLocation,
		 EndLocation,
		 ECollisionChannel::ECC_Camera))
	{
		 HitLocation = HitResult.Location;
			 return true;
	}
	 HitLocation = FVector(0);
	 return false; // Line trace didn't succeed
	
 }

 void ATankPlayerController::SetPawn(APawn* InPawn)
 {
	 Super::SetPawn(InPawn);

	 if (InPawn)
	 {
		 auto PossessedTank = Cast<ATank>(InPawn);
		 if (!ensure(PossessedTank)) { return; }

		 PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	 }
 }

 void ATankPlayerController::OnPossedTankDeath()
 {
	 UE_LOG(LogTemp, Warning, TEXT("Recieved!"))

	 StartSpectatingOnly();
 }