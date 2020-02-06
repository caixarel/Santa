// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacaCimaBaixo.generated.h"

UCLASS()
class OUTRO2D_API APlacaCimaBaixo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlacaCimaBaixo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector direction;
	int distancia;
	float TempoExecucao;
	float alturaDelta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Velocidade=500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DuracaoDoMovimento = 1.5f;
};
