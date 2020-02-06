// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemMoeda.generated.h"


UCLASS()
class OUTRO2D_API AItemMoeda : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemMoeda();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void Colission(AActor* Actor, AActor* OtherActor);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sprite")
		class UPaperSpriteComponent* Sprite;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
