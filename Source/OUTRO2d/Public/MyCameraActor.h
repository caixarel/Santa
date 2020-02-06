// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MyCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class OUTRO2D_API AMyCameraActor : public ACameraActor
{
	GENERATED_BODY()
public:
    AMyCameraActor();
    UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "Camera")
        class UCameraComponent* CameraPersonagem;
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    

};
