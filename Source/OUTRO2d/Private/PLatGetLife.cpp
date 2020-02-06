// Fill out your copyright notice in the Description page of Project Settings.


#include "PLatGetLife.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include"ItemVida.h"
#include"MyGameInstance.h"
#include"Outro.h"
#include"Kismet/GameplayStatics.h"


// Sets default values
APLatGetLife::APLatGetLife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorHit.AddDynamic(this, &APLatGetLife::Collision2);
	OnActorBeginOverlap.AddDynamic(this, &APLatGetLife::Overlapp2);
}

// Called when the game starts or when spawned
void APLatGetLife::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLatGetLife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APLatGetLife::Collision2(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AOutro* outro = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this, 0));
	bool jumping = outro->bSalto;
	//when this actor is hit
	if (bCanSpawn && jumping)
	{
		FVector spawnLife = GetActorLocation();
		spawnLife.Z += 100;
		UWorld* World = GetWorld();
		//Spawns other actor to that gives 1 life to the character
		World->SpawnActor<AItemVida>(EnemyBlueprint, spawnLife, FRotator::ZeroRotator);
		UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
		int lifes=gameinstance->Vidas;
		bCanSpawn = false;
	}
	
}

void APLatGetLife::Overlapp2(AActor* actor, AActor* otheractor)
{
	if (otheractor->ActorHasTag("Mau"))
	{
		otheractor->Destroy();
	}
	

}

