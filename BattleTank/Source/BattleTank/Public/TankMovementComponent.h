// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"


#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;






/**
 * Responsible for driving Tanks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
