// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevel.h"
#include"PaperSprite.h"
#include"kismet/GameplayStatics.h"
#include"PaperSpriteComponent.h"
#include"UObject/ConstructorHelpers.h"
#include"Components/BoxComponent.h"
#include "Engine/Engine.h"
#include"OUTRO2dGameModeBase.h"
#include "MyGameInstance.h"

// Sets default values
ANextLevel::ANextLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Caixa = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Caixa->InitBoxExtent(FVector(70.f, 50.f, 50.f));
	RootComponent=Caixa;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("name"));
	Sprite->SetupAttachment(RootComponent);

	
	FRotator rotation= GetActorRotation();
	rotation.Yaw += 90;
	SetActorRotation(rotation);

	OnActorBeginOverlap.AddDynamic(this, &ANextLevel::Overlapwin);

	
	
}

void ANextLevel::Overlapwin(AActor* actor, AActor* otheractor)
{

	//when this actor is overlapped by the character the next Level will be loaded
	UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
	gameinstance->ChangeMap();
}

// Called when the game starts or when spawned
void ANextLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANextLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

