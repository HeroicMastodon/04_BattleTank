// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"SprungWheel.h"






#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"



// Used to set max driving force, and to apply forces to the Tank
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Assume 40 ton tank, and 1g accleration
	
	virtual void BeginPlay() override;

private:
	UTankTrack();

	void DriveTrack(float CurrentThrottle);

	TArray<ASprungWheel*> GetWheels() const;

};
