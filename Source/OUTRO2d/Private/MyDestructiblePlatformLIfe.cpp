// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDestructiblePlatformLIfe.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include"ItemVida.h"
#include "Engine/World.h"


AMyDestructiblePlatformLIfe::AMyDestructiblePlatformLIfe() {
	PrimaryActorTick.bCanEverTick = true;
	OnActorHit.AddDynamic(this, &ADestructiblePlatform::Collision);
	OnActorBeginOverlap.AddDynamic(this, &ADestructiblePlatform::Overlapp);
}
void AMyDestructiblePlatformLIfe::Collision2(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector location = GetActorLocation();
	location.Z += 10;
	SetActorLocation(location);
	FVector spawnLife = location;
	spawnLife.Z += 20;
	UWorld* World = GetWorld();
	World->SpawnActor<AItemVida>(EnemyBlueprint, spawnLife, FRotator::ZeroRotator);


	//GetWorldTimerManager().SetTimer(DestroyTemp, this, &ADestructiblePlatform::destroy, 0.1f, false);
}

void AMyDestructiblePlatformLIfe::Overlapp2(AActor* actor, AActor* otheractor)
{
	otheractor->Destroy();

}


