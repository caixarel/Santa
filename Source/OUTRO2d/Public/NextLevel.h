// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevel.generated.h"

UCLASS()
class OUTRO2D_API ANextLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANextLevel();

	UFUNCTION()
		void Overlapwin(AActor* actor,AActor* otheractor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="name")
	class UPaperSpriteComponent* Sprite;
	UPROPERTY(EditAnywhere, Category = "name")
		class UBoxComponent* Caixa;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FName> Level = { TEXT("Mapa2"),TEXT("Mapa3") };
	
	

};
