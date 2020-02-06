// Fill out your copyright notice in the Description page of Project Settings.


#include "resetPoint.h"
#include"MyGameInstance.h"
#include"Components/BoxComponent.h"
#include "Engine/Engine.h"


// Sets default values
AresetPoint::AresetPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//collider will be used to store a safe position for the character to be spawned
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Collider->InitBoxExtent(FVector(10.f, 10.f, 500.f));
	RootComponent = Collider;

	OnActorBeginOverlap.AddDynamic(this, &AresetPoint::Collision);
}

// Called when the game starts or when spawned
void AresetPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AresetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AresetPoint::Collision(AActor* actor, AActor* otheractor)
{
	//when the character overlapps this actor a position will be stored
	FVector ResetLocation =( actor->GetActorLocation());
	UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
	//this position will be used to spawn the character to safe position if he fall on the Holes of the level
	gameinstance->PlayerRestartLocation= ResetLocation;
}

