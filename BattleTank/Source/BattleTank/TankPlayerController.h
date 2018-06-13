// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
  
 




UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:

	ATank * GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly) 
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333333;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
