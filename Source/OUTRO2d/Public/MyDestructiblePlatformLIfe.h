// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructiblePlatform.h"
#include "MyDestructiblePlatformLIfe.generated.h"

/**
 * 
 */
UCLASS()
class OUTRO2D_API AMyDestructiblePlatformLIfe : public ADestructiblePlatform
{
	GENERATED_BODY()
public:
	AMyDestructiblePlatformLIfe();

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AItemVida>EnemyBlueprint;

	UFUNCTION()
		void Collision2(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void Overlapp2(AActor* actor, AActor* otheractor);
	FTimerHandle DestroyTemp;
	
	

};
