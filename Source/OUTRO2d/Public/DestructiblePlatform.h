// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructiblePlatform.generated.h"

UCLASS()
class OUTRO2D_API ADestructiblePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructiblePlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "collisionbox")
		class UBoxComponent* Box;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void Overlapp(AActor* actor, AActor* otheractor);
	FTimerHandle DestroyTemp;
	UFUNCTION()
		void destroy();
	UFUNCTION()
		void ComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
