// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisibleFloor.generated.h"

UCLASS()
class OUTRO2D_API AInvisibleFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvisibleFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Colisao(AActor* Selfactor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
