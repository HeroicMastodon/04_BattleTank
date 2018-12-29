// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "BattleTank.h"
#include "GameFrameWork/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
// Depends on movement comopnent via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); 

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
	
};


void ATankAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Recieved!"));

	if (!GetPawn())
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}
