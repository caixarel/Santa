// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleFloor.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include"MyGameInstance.h"


// Sets default values
AInvisibleFloor::AInvisibleFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorHit.AddDynamic(this, &AInvisibleFloor::Colisao);
}

// Called when the game starts or when spawned
void AInvisibleFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvisibleFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AInvisibleFloor::Colisao(AActor* Selfactor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//this actor represents a Hole in the map where the character can fall and by consequence loses 1 life
	UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
	//if lives are less or equal to 0 is GameOver
	if (gameinstance->Vidas<=0)
	{
		OtherActor->Destroy();
		gameinstance->RestartGame();
	}
	else
	{
		//character loses 1 life and respawns in a safe location
		gameinstance->Vidas--;
		gameinstance->Respawn();
		
	}
}


