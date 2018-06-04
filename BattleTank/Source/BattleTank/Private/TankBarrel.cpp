// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	/// move the barrel the right amount this frame
	/// given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel-elavate() called"))
}

