// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include"Kismet/GameplayStatics.h"
#include"Outro.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

	//when the player reaches the end of the map this function will be activated
void UMyGameInstance::ChangeMap()
{
	
	MapCount++;//variable increments 
	FName nivel = Level[MapCount];//the Variable nivel will be the Fname stored on the array Level
	//the Mapcount will be used as a index for the array
	
	UGameplayStatics::OpenLevel(this, nivel, false);//the new map will be loaded
}

float UMyGameInstance::GanharVida(float vida)
{
	//if bool is true the player will gain life
	if (bcanGainLife)
	{
		Vidas += vida;
		//set the boolean to false to prevent the player of gainning multiple lifes
		bcanGainLife = false;
		//
		GetTimerManager().SetTimer(lifeTemp, this, &UMyGameInstance::CanGainLife, 0.1f);
	}
	return Vidas;

}

float UMyGameInstance::GanharMoedas(float money)
{
	
	Moedas += money;
	//if the amount of Moedas is equal to 10
	if (Moedas==10)
	{
		AOutro* outro = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this,0));
		outro->bShootMode=true; // shootMode will be activated allowing the player to shoot balls
		//number of Moedas will go back to 0
		Moedas = 0;
		//ShootMode will be active for 30 seconds
		GetTimerManager().SetTimer(ShootMode, this, &UMyGameInstance::StopShootMode, 30.1f);

	}
	return Moedas;
}
//when the player looses all his lifes he will go to the GameOver menu where the player can choose to play again
//this function will set the stats and the map to their initial values
void UMyGameInstance::RestartGame()
{
	Vidas = 3;
	Moedas = 0;
	UGameplayStatics::OpenLevel(this, "MapaGameOver", true);
}
//when the actor falls on a hole he will be placed on a safe location
void UMyGameInstance::Respawn()
{
	FName nivel = Level[(MapCount)];
	AOutro* Outro = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Outro->SetActorLocation(PlayerRestartLocation);
}

void UMyGameInstance::CanGainLife()
{
	//player can gain life
	bcanGainLife = true;
}


void UMyGameInstance::StopShootMode()
{
	//ends the ShootMode
	AOutro* outro = Cast<AOutro>(UGameplayStatics::GetPlayerCharacter(this, 0));
	outro->bShootMode = false;
}


