// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMoeda.h"
#include"Outro.h"
#include"Kismet/GameplayStatics.h"
#include"PaperCharacter.h"
#include "GameFramework/Actor.h"
#include"PaperSpriteComponent.h"
#include"PaperSprite.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include"MyGameInstance.h"






// Sets default values
AItemMoeda::AItemMoeda()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	Sprite->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UPaperSprite>Forma(TEXT("PaperSprite'/Game/Materias_Mapa/bonus2_Sprite.bonus2_Sprite'"));
	if (Forma.Succeeded())
	{
		
		Sprite->SetSprite(Forma.Object);
	}

	OnActorBeginOverlap.AddDynamic(this, &AItemMoeda::Colission);
}

// Called when the game starts or when spawned
void AItemMoeda::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemMoeda::Colission(AActor* Actor, AActor* OtherActor)
{
	UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
	gameinstance->GanharMoedas(1);
	Destroy();
}

// Called every frame
void AItemMoeda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

