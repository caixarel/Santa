// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OUTRO2D_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Vidas = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Moedas = 0;
	//this array stores the name of the maps
	//this will allow to change the levels
	TArray<FName> Level = { TEXT("Mapa1"),TEXT("Mapa2") ,TEXT("Mapa3") };

	FTimerHandle lifeTemp;
	FTimerHandle Canshoot;
	FTimerHandle ShootMode;

	//
	bool bcanGainLife = true;
	//the game will start on the first map of the array
	//when the first level ends this variable will be incremented and will change the level of the game
	int MapCount = 0;
	//this Fvector will store a location where the player will respawn in case he falls on the holes of the maps
	FVector PlayerRestartLocation;

	void ChangeMap();
	UFUNCTION()
		float GanharVida(float vida);//function used to gain or lose lifes
	UFUNCTION()
		float GanharMoedas(float money);//function to gain coins
	UFUNCTION()
		void RestartGame();
	UFUNCTION()
		void Respawn();
	UFUNCTION()
		void CanGainLife();
	UFUNCTION()
		void StopShootMode();
private:

protected:
	
	
};
