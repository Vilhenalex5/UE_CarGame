// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointManager.generated.h"

UCLASS()
class FIRSTPROJECT_API ACheckPointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPointManager();

	UFUNCTION(BlueprintCallable)
	void NotifyCheckpointCrossed(AController* Controller, AActor* Checkpoint);

	UFUNCTION(BlueprintCallable)
	void RegisterPlayer(AController* ControllerToRegister);

protected:

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> Checkpoints;

	UPROPERTY()
	TMap<AController*, int> PlayerCheckpointTracker;
};
