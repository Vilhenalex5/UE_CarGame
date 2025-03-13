// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointManager.h"
#include "ChaosWheeledVehicleMovementComponent.h"

// Sets default values
ACheckPointManager::ACheckPointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACheckPointManager::NotifyCheckpointCrossed(AController* Controller, AActor* Checkpoint)
{
	int* CheckpointTracker = PlayerCheckpointTracker.Find(Controller);

	if (!CheckpointTracker)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, "Player Not Found");
		return;
	}

	if (Checkpoints[*CheckpointTracker] == Checkpoint)
	{
		PlayerCheckpointTracker[Controller] = FMath::Wrap(*CheckpointTracker + 1, -1, Checkpoints.Num() - 1);	
	}
	else
	{

		int PreviousCheckpointIndex = *CheckpointTracker - 1;
		PreviousCheckpointIndex = FMath::Wrap(PreviousCheckpointIndex, - 1, Checkpoints.Num() - 1);
		AActor* CheckpointActor = Checkpoints[PreviousCheckpointIndex];

		APawn* ControllerPawn = Controller->GetPawn();

		UChaosWheeledVehicleMovementComponent* VehicleComponent = Cast<UChaosWheeledVehicleMovementComponent>(ControllerPawn->GetComponentByClass(UChaosWheeledVehicleMovementComponent::StaticClass()));
		VehicleComponent->ResetVehicleState();
		ControllerPawn->SetActorLocationAndRotation(CheckpointActor->GetActorLocation(), CheckpointActor->GetActorRotation(), false, nullptr, ETeleportType::TeleportPhysics);
	}

}


void ACheckPointManager::RegisterPlayer(AController* ControllerToRegister)
{
	PlayerCheckpointTracker.Add(ControllerToRegister, 0);
}



