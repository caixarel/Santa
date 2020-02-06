// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Balas.generated.h"

UCLASS()
class OUTRO2D_API ABalas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Corpo")
		class UPaperSpriteComponent* Corpo;
	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Corpo")
		class USphereComponent* Sphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Collision(AActor* actor, AActor* otheractor);

};
