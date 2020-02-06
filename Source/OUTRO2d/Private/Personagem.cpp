// Fill out your copyright notice in the Description page of Project Settings.


#include "Personagem.h"
#include"Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include"GameFramework/PawnMovementComponent.h"
#include"MyCharacter.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include"PaperFlipbookComponent.h"
#include"PaperFlipbook.h"
#include"UObject/ConstructorHelpers.h"
#include"MyGameInstance.h"



// Sets default values
APersonagem::APersonagem()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Capsula = CreateDefaultSubobject<UBoxComponent>(FName("SOcket"));
	RootComponent = Capsula;
	
	Capsula2 = CreateDefaultSubobject<UBoxComponent>(FName("CapsuleCollision"));
	Capsula2->SetupAttachment(RootComponent);
	Capsula2->InitBoxExtent(FVector(10.f, 20.f, 10.f));

	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Walk"));
	flipBook->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UPaperFlipbook>Animation(TEXT("PaperFlipbook'/Game/yeti/walk.walk'"));

	if ( Animation.Succeeded())
	{
		
		flipBook->SetFlipbook(Animation.Object);
	}
	TempoExecucao = 0.0f;
	alturaDelta = 0.0f;
	//actor must be able to fall down from other objects
	Capsula->SetSimulatePhysics(true);
	//this locks the rotation and the translation of the actor components to avoid him from falling from the map
	Capsula->BodyInstance.bLockXTranslation = true;
	Capsula->BodyInstance.bLockRotation = true;
	Capsula2->BodyInstance.bLockXTranslation = true;
	Capsula2->BodyInstance.bLockRotation = true;
	flipBook->BodyInstance.bLockXTranslation = true;
	flipBook->BodyInstance.bLockRotation = true;
	
	
	Capsula2->OnComponentBeginOverlap.AddDynamic(this, &APersonagem::Collision);
	Capsula2->OnComponentHit.AddDynamic(this, &APersonagem::BodyCollision);


}

// Called when the game starts or when spawned
void APersonagem::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void APersonagem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = GetActorRotation();
	direction = this->GetActorLocation();
	//the Sin formula will oscilate between a positive and negative value and this value will be uses to change the
	//direction of movement for the actor
	alturaDelta = (FMath::Sin(TempoExecucao + (DeltaTime)) - FMath::Sin(TempoExecucao));
	direction.Y += alturaDelta * Velocidade;
	TempoExecucao += (DeltaTime * DuracaoDoMovimento);
	this->SetActorLocation(direction);
	//the animation of the ator must always face his direction of movement
	if (alturaDelta<0)
	{
		rotation.Yaw += 90.f;
		flipBook->SetRelativeRotation(rotation);
	}
	else
	{
		rotation.Yaw += 270.f;
		flipBook->SetRelativeRotation(rotation);
	}
}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}




