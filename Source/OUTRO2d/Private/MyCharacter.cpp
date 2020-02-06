// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include"Components/CapsuleComponent.h"
#include"Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include"GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include"GameFramework/PawnMovementComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include"Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include"Components/BillboardComponent.h"
#include"DrawDebugHelpers.h"
#include"WorldCollision.h"
#include"Engine/World.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = true;
	Capsula = CreateDefaultSubobject<UCapsuleComponent>(FName("Colisor"));
	Capsula->SetCapsuleRadius(40.f);
	Capsula->SetCapsuleHalfHeight(60.f);
	RootComponent = Capsula;*/
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringCamera"));
	SpringArmCamera->TargetArmLength = 1000.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->bEnableCameraLag = true;
	SpringArmCamera->CameraLagSpeed = 40.f;
	SpringArmCamera->SetupAttachment(RootComponent);

	CameraPersonagem = CreateDefaultSubobject<UCameraComponent>(FName("CameraPersonagem"));
	CameraPersonagem->SetupAttachment(SpringArmCamera);
	
	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->GravityScale = 1.5f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	OnActorBeginOverlap.AddDynamic(this, &AMyCharacter::Morre);
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Direita(float Eixo)
{
	AddMovementInput(GetActorRightVector() * Eixo);
}

void AMyCharacter::Salto()
{
	if (GetCharacterMovement()->IsMovingOnGround() == true)
	{
		ResetSalto();
	}
	if (GetCharacterMovement()->IsMovingOnGround() == true && Saltos<1)
	{
		bPressedJump = true;
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FromInt(Saltos), true);
		bPressedJump = true;
	}
	else if (GetCharacterMovement()->IsMovingOnGround() == false && Saltos < 1)
	{
		SaltaUmaVez();
	}
}

void AMyCharacter::AcabouSalto()
{
	
	bPressedJump = false;
}

void AMyCharacter::SaltaUmaVez()
{
		if (bSalto)
		{
			if (Saltos < 1)
			{
				GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FromInt(Saltos), true);

				LaunchCharacter(FVector(0.f, 0.f, 1) * 700, false, true);
			}

			Saltos++;


			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::FromInt(Saltos), true);
			return;
		}
		else
		{
			return;
		}
}

void AMyCharacter::ResetSalto()
{
	bSalto = true;
	Saltos = 0;
	return;
}


void AMyCharacter::OnOverlapBegins(AActor* actor, AActor* otherActor)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString(TEXT("alooo")), true);
	Destroy();

	if (GetCharacterMovement()->IsMovingOnGround() == true)
	{
		Destroy();
	}
	else if (otherActor->ActorHasTag("MAU"))
	{
		otherActor->Destroy();
	}
	
}
void AMyCharacter::Morre(AActor* actor, AActor* otherActor)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString(TEXT("alooo")), true);
	Destroy();

	if (GetCharacterMovement()->IsMovingOnGround() == true)
	{
		Destroy();
	}
	else if (otherActor->ActorHasTag("MAU"))
	{
		otherActor->Destroy();
	}

}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Direita", this, &AMyCharacter::Direita);
	PlayerInputComponent->BindAction("Salto", EInputEvent::IE_Pressed, this, &AMyCharacter::Salto);
	PlayerInputComponent->BindAction("Salto", EInputEvent::IE_Released, this, &AMyCharacter::AcabouSalto);
}

