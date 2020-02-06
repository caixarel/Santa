// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraActor.h"
#include"Outro.h"
#include "Camera/CameraComponent.h"
#include"Components/InputComponent.h"
#include"Kismet/GameplayStatics.h"


AMyCameraActor::AMyCameraActor() 
{
	PrimaryActorTick.bCanEverTick = true;
	/*CameraPersonagem=CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	RootComponent = CameraPersonagem;*/

}
void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();

}

void AMyCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AOutro* outro = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (outro!=nullptr)
	{
		//camera will follow the character but will always keep it's X and Z position
		float outroLocation = outro->GetActorLocation().Y;	
		this->SetActorLocation(FVector(-1350.f, (outroLocation), 4009.F));
	}
	
}
