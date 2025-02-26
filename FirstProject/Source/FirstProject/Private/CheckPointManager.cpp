// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointManager.h"

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
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, "GOODDD BOY");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, "BAAAAD BOY");
	}

}

void ACheckPointManager::RegisterPlayer(AController* ControllerToRegister)
{
	PlayerCheckpointTracker.Add(ControllerToRegister, 0);
}


