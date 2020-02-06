// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInvencivel.generated.h"

UCLASS()
class OUTRO2D_API AItemInvencivel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemInvencivel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void Collision(AActor* Actor, AActor* otherActor);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "corpo")
		class UPaperSpriteComponent* Corpo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
