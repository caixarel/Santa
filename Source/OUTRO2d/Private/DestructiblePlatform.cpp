// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructiblePlatform.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"



// Sets default values
ADestructiblePlatform::ADestructiblePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//collider setup
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);
	Box->InitBoxExtent(FVector(10.f, 30.f, 15.f));
	
	Box->OnComponentHit.AddDynamic(this, &ADestructiblePlatform::ComponentHit);
	OnActorBeginOverlap.AddDynamic(this, &ADestructiblePlatform::Overlapp);
	
}

// Called when the game starts or when spawned
void ADestructiblePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructiblePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructiblePlatform::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector location = GetActorLocation();
	//when hit the actor will move upwards , if he overlapps an enemy the enemy will be destroyed
	location.Z += 30;
	SetActorLocation(location);
	//actor is destroyed 0.1 seconds after being hit
	GetWorldTimerManager().SetTimer(DestroyTemp, this, &ADestructiblePlatform::destroy, 0.1f, false);
}
//when this actor overlaps an enemy collider the other actor actor will be destroyed
void ADestructiblePlatform::Overlapp(AActor* actor, AActor* otheractor)
{
	otheractor->Destroy();
}
void ADestructiblePlatform::destroy()
{
	Destroy();
}