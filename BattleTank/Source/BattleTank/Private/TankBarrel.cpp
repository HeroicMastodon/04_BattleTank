// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "BattleTank.h"
#include "Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	// given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	
	/*auto Speed = GetWorld()->DeltaTimeSeconds;
	UE_LOG(LogTemp, Error, TEXT("speed = %f"), Elevation)*/

}

