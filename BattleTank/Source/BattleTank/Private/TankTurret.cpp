// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	// given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	//auto Elevation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(0, NewRotation, 0));


	/*auto Speed = GetWorld()->DeltaTimeSeconds;
	UE_LOG(LogTemp, Error, TEXT("speed = %f"), Elevation)*/

}

