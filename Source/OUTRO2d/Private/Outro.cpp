// Fill out your copyright notice in the Description page of Project Settings.


#include "Outro.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include"GameFramework/CharacterMovementComponent.h"//getmovement
#include"Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectBaseUtility.h"
#include "GameFramework/NavMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include"Kismet/GameplayStatics.h"
#include"MyGameInstance.h"
#include"PaperFlipbook.h"
#include"PaperFlipbookComponent.h"
#include"UObject/ConstructorHelpers.h"
#include"MyGameInstance.h"
#include"Particles/ParticleSystemComponent.h"
#include"Particles/ParticleSystem.h"
#include"Balas.h"



// Sets default values
AOutro::AOutro()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//setup of the spring arm for the camera


	//setup details for the character moevement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	OnActorBeginOverlap.AddDynamic(this, &AOutro::Colisao);
	OnActorEndOverlap.AddDynamic(this, &AOutro::FimEscada);

	
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	//will constrain the movement of the character on the x axis to prevent him from falling off the map
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
	
	//setup for the character animation
	animation = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("corpo"));
	animation->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UPaperFlipbook>flipbook(TEXT("PaperFlipbook'/Game/sprites/Run.Run'"));
	if (flipbook.Succeeded())
	{
		animation->SetFlipbook(flipbook.Object);
		animation->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		animation->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	//setup for the particle system that will be activated if the player is in Invencible mode
	Particulas = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particles"));
	Particulas->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UParticleSystem>Fire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (Fire.Succeeded())
	{
		Particulas->SetTemplate(Fire.Object);
		Particulas->SetVisibility(false);
		Particulas->SetRelativeScale3D(FVector(10.f, 1.f, 10.f));
	}
	//the Flipbook components should have a Block collision response 
	animation->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//the character can not rotate
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	
}

// Called when the game starts or when spawned
void AOutro::BeginPlay()
{
	Super::BeginPlay();
	//sets the direction of the animation on the beginning of the game
	bIsMovingRight = true;
	animation->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
			
}

void AOutro::Direita(float Eixo)
{
	//checks the input received
	//if input is positive the player is moving to the right 
	if (Eixo>0)
	{
		bIsMovingRight = true;
		//rotation of the animation is facing right
		animation->SetVisibility(true);
		animation->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	}
	//if input is negative the player is moving to the left 
	else if(Eixo<0)
	{
		bIsMovingRight = false;
		animation->SetVisibility(true);

		//rotation of the animation is facing Left
		animation->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	}
	//moves the character to the left or to the right depending of the input received
	FVector location = GetActorLocation();
	location.Y += Eixo*10;
	SetActorLocation(location);
	
}

void AOutro::Salto()
{
	//if the character is touching a surface he can jump
	if (GetCharacterMovement()->IsMovingOnGround() == true)
	{
		ResetSalto();
	}
	//the character is able to do a double jump
	if (GetCharacterMovement()->IsMovingOnGround() == true && Saltos < 1)
	{ 
		//player jumps
		bPressedJump = true;
		//0.5seconds after the start of the jump the character will be able to kill enemys
		GetWorldTimerManager().SetTimer(Temporizador, this, &AOutro::Matar, 0.5f, false);
	}
	//if the character is already jumping we will be able to perform a additional jump
	else if (GetCharacterMovement()->IsMovingOnGround() == false && Saltos < 1)
	{
		SaltaUmaVez();
	}
}

void AOutro::AcabouSalto()
{
	bPressedJump = false;
}

void AOutro::SaltaUmaVez()
{
	//if boollean to allow jump is true
	if (bSalto)
	{
		//if the variable saltos is less than 1
		if (Saltos < 1)
		{
			//the character will be launched on the air performing a double jump
			LaunchCharacter(FVector(0.f, 0.f, 1) * 700, false, true);
		}
		//the variable jump will increment and will be equal to 1 so the character cannot jump anymore 
		Saltos++;
		return;
	}
	else
	{
		return;
	}
}
//when the character is touching ground the jump is reset and now he can jump again
void AOutro::ResetSalto()
{
	GetWorldTimerManager().ClearTimer(Temporizador);
	PodeMatar = false;//character can not kill 
	bSalto = true;//character can jump
	Saltos = 0;//jump count equals 0
	return;
}
//when a collision is detected
void AOutro::Colisao(AActor* Actor, AActor* OtherActor)
{
	// if character is invencivle and the other actor has tag "MAU"
	if (bIsInvencible && OtherActor->ActorHasTag("Mau"))
	{
		//other actor will be destroyed
		OtherActor->Destroy();
	}
	//if not invencible
	else
	{
		if ((OtherActor->ActorHasTag("Mau")) || (OtherActor->ActorHasTag("escada")) )
		{
			
			//if other actor has tag "escada"(ladder) 
			if (OtherActor->ActorHasTag("escada"))
			{
				bPodeSubir = true;//character can climb the ladder
			}
			//if the character is on the ground he cannot kill the enemys
			//when the character is on the ground and collides with an enemy
			else if ((GetCharacterMovement()->IsMovingOnGround() == true )&& (bCanDie))
			{
				UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());
				int lives = gameinstance->Vidas;
				//character loses 1 life
				gameinstance->GanharVida(-1);
				//if the lives are equal or less than 0 the character will be destroyed and the game goes to the GameOver Menu
				if (lives <= 0)
				{
					Destroy();
					gameinstance->RestartGame();
				}
				else 
				{
					UMyGameInstance* gameinstance = Cast<UMyGameInstance>(GetGameInstance());

					//after colliding with and enemy the character cannot lose more lifes for 2 seconds
					bCanDie = false;
					GetWorldTimerManager().SetTimer(CandieTemp, this, &AOutro::CanDie, 2.f, false);
				}

			}
			//character is on the air for more than 0.5 seconds so he can kill enemys
			else if (PodeMatar)
			{
				//destroy other actor
				OtherActor->Destroy();
				UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance());
				//when enemys are destroyed the character gains 1 coin an then is launched in the air
				gameInstance->GanharMoedas(1);
				LaunchCharacter(FVector(0.f, 0.f, 1) * 700, false, true);
			}
		}
	}	
}
//
void AOutro::Dashing()
{
	if (bIsMovingRight)
	{
		if (bCanDash)
			{
			//character will dash forward
				LaunchCharacter(FVector(0.0f, 2.0f, 0.0f) * 600, false, true);
				bCanDash = false;
				//character cannot dash again for 3 seconds
				GetWorldTimerManager().SetTimer(Dash, this, &AOutro::FazerDash, 3.f, false);
			}
	}
	else//character moving to the left
	{
		if (bCanDash)
		{
			LaunchCharacter(FVector(0.0f, 2.0f, 0.0f) * -600, false, true);
			bCanDash = false;
			GetWorldTimerManager().SetTimer(Dash, this, &AOutro::FazerDash, 3.f, false);
		}
	}
}
//kill function
void AOutro::Matar()
{
	//can kill
	PodeMatar = true;
}

void AOutro::FazerDash()
{
	//can dash
	bCanDash = true;
	GetWorldTimerManager().ClearTimer(Dash);
}
//climb ladder
void AOutro::SubirEscada(float Eixo)
{
	//if the character is in the ladder but is not receiving input to go up or down it will stay still
	if (Eixo==0 && bPodeSubir)
	{
		GetCharacterMovement()->GravityScale = 0.f;
	}
	//character climbs down the ladder
	else if ((GetCharacterMovement()->IsMovingOnGround()==false) && Eixo<0 && bPodeSubir)
	{
	FVector Location = GetActorLocation();
	Location.Z += Eixo * subir;
	SetActorLocation(Location);
	}
	//character climbs up the ladder
	else if (bPodeSubir && Eixo>0)
	{
		//character movement set to flying to allow the player to climb the ladder with being dragged down by gravity
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		FVector Location = GetActorLocation();
		Location.Z += Eixo*subir;
		SetActorLocation(Location);
	}	
}
//end of the ladder
void AOutro::FimEscada(AActor* Actor, AActor* OtherActor)
{
	//cannot climb the ladder anymore
	bPodeSubir = false;
	//movement is set back to walking
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCharacterMovement()->GravityScale = 2.f;

}

void AOutro::Shoot()
{
	if (bShootMode)
	{
		if (bcanShoot)
		{
			FVector locationBall = GetActorLocation();
			locationBall.Y += 100;
			//character will shoot balls
			GetWorld()->SpawnActor<ABalas>(SHootBall, locationBall, FRotator::ZeroRotator);
			bcanShoot = false;
			//can only shoot again in 0.5 seconds
			GetWorldTimerManager().SetTimer(canshootball, this, &AOutro::EndShoot, 0.5f, false);
		}
	}
}

void AOutro::EndShoot()
{
	//can no longer shoot
	bcanShoot = true;
	
}

// Called every frame
void AOutro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool jump = GetCharacterMovement()->IsMovingOnGround();
	//if the character was hit by an enemy the animation will be set as visible or invisible
	//this way the player knows that he was hit and that he cannot die for 3 seconds
	if (bCanDie==false)
	{
		time = time + 1;
		if (time%4==0){animation->SetVisibility(false);}
		else if (time>121){time = 0;}
		else { animation->SetVisibility(true); }
	}
	
}

// Called to bind functionality to input
void AOutro::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Direita", this, &AOutro::Direita);
	PlayerInputComponent->BindAction("Salto", EInputEvent::IE_Pressed, this, &AOutro::Salto);
	PlayerInputComponent->BindAction("Salto", EInputEvent::IE_Released, this, &AOutro::AcabouSalto);
	PlayerInputComponent->BindAction("Disparar", EInputEvent::IE_Released, this, &AOutro::Dashing);
	PlayerInputComponent->BindAxis("Subir", this, &AOutro::SubirEscada);
	PlayerInputComponent->BindAction("Snowball",EInputEvent::IE_Pressed ,this, &AOutro::Shoot);

}




//invencibility function
bool AOutro::EstaInvencivel(bool invencivel)
{

	bIsInvencible = invencivel;
	//if bIsInvencible== true then the particule system will be activated during 20 seconds
	Particulas->SetVisibility(true);
	GetWorldTimerManager().SetTimer(Invencibilidade, this, &AOutro::JaNaoEstaInvencivel, 20.f, false);
	return bIsInvencible;
}

void AOutro::JaNaoEstaInvencivel()
{
	//no longer Invencible 
	bIsInvencible = false;
	GetWorldTimerManager().ClearTimer(Invencibilidade);
	Particulas->SetVisibility(false);

}

void AOutro::CanDie()
{
	GetWorldTimerManager().ClearTimer(CandieTemp);
	bCanDie = true; 
	animation->SetVisibility(true);
}

