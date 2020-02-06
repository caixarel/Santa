// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemVida.h"
#include"Outro.h"
#include "Kismet/GameplayStatics.h"
#include"MyGameInstance.h"



// Sets default values
AItemVida::AItemVida()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &AItemVida::Collision);
}

// Called when the game starts or when spawned
void AItemVida::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemVida::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemVida::Collision(AActor* Actor, AActor* otherActor)
{
	if (otherActor->ActorHasTag("Player"))
	{
		UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());

			gameinstance->GanharVida(1);
			Destroy();
	}
	
}

