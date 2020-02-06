// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacaCimaBaixo.h"
#include "GameFramework/Actor.h"


// Sets default values
APlacaCimaBaixo::APlacaCimaBaixo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//TempoExecucao is the amount of time where the actor will float in each direction
	TempoExecucao = 0.0f;
	//alturaDelta will be positive or negative . this is used to move the actor to the right side when is positive 
	//or to the left side when negative
	alturaDelta = 0.0f;
	direction = FVector(0.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void APlacaCimaBaixo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlacaCimaBaixo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	direction = this->GetActorLocation();
	//Sin formula will have a positive or negative value
	alturaDelta = (FMath::Sin(TempoExecucao + (DeltaTime)) - FMath::Sin(TempoExecucao));
	//this will tell the actor to move in a certain direction for a certain amount
	direction.Z += alturaDelta * Velocidade;
	TempoExecucao += (DeltaTime * DuracaoDoMovimento);
	this->SetActorLocation(direction);
}

