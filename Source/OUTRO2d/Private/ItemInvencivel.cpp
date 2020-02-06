// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInvencivel.h"
#include"Outro.h"
#include"kismet/GameplayStatics.h"
#include"PaperCharacter.h"
#include"PaperSpriteComponent.h"
#include"UObject/ConstructorHelpers.h"
#include"PaperSprite.h"

// Sets default values
AItemInvencivel::AItemInvencivel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//sprite setup
	Corpo = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CorpoInvencivel"));
	Corpo->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UPaperSprite>Raio(TEXT("PaperSprite'/Game/Materias_Mapa/lightning_Sprite.lightning_Sprite'"));
	if (Raio.Succeeded())
	{
		Corpo->SetSprite(Raio.Object);
	}

	OnActorBeginOverlap.AddDynamic(this, &AItemInvencivel::Collision);

}

// Called when the game starts or when spawned
void AItemInvencivel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemInvencivel::Collision(AActor* Actor, AActor* otherActor)
{
	//when the Character collides with this actor , character becomes invencible and this actor is destroyed
	AOutro* Personage = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Personage->EstaInvencivel(true);
	Destroy();
}

// Called every frame
void AItemInvencivel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

