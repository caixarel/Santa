// Fill out your copyright notice in the Description page of Project Settings.


#include "Balas.h"
#include"Outro.h"
#include"PaperSprite.h"
#include"PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h"
#include"Components/SphereComponent.h"
#include"MyGameInstance.h"

// Sets default values
ABalas::ABalas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//collision setup
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(5.f);
	RootComponent = Sphere;
	//sprite setup
	Corpo = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CorpoDaBola"));
	Corpo->SetupAttachment(RootComponent);

	//Choosing what will be the sprite for this actor
	ConstructorHelpers::FObjectFinder<UPaperSprite>Bola(TEXT("PaperSprite'/Game/Materias_Mapa/5e0f4a61163dd_Sprite.5e0f4a61163dd_Sprite'"));
	if (Bola.Succeeded())
	{
		Corpo->SetSprite(Bola.Object);
	}

	OnActorBeginOverlap.AddDynamic(this, &ABalas::Collision);

}

// Called when the game starts or when spawned
void ABalas::BeginPlay()
{
	Super::BeginPlay();
	//this actor will be destroyed after 2 seconds
	SetLifeSpan(2);
}

// Called every frame
void ABalas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//actor will move along the X axis 
	FVector location = GetActorLocation();
	FVector frente = GetActorForwardVector();
	location.Y += 30;
	SetActorLocation(location);

}

void ABalas::Collision(AActor* actor, AActor* otheractor)
{
	//if there is a collision with an actor with the tag "Mau" 
	if (otheractor->ActorHasTag("Mau"))
	{
		//will destroy the other actor and will increment the Moedas(coins) by one
		otheractor->Destroy();
		UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
		gameinstance->GanharMoedas(1);
	}
}

