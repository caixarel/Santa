// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLatGetLife.generated.h"

UCLASS()
class OUTRO2D_API APLatGetLife : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APLatGetLife();

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AItemVida>EnemyBlueprint;
	bool bCanSpawn = true;
	
	FTimerHandle DestroyTemp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Collision2(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void Overlapp2(AActor* actor, AActor* otheractor);

};
