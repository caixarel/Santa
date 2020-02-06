// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OUTRO2dGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OUTRO2D_API AOUTRO2dGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AOUTRO2dGameModeBase();
	TArray<FName> Level = { TEXT("Mapa2"),TEXT("Mapa3") ,TEXT("Mapa3") };
	void ChangeMap();
	
private:
protected:
	virtual void BeginPlay() override;
	int MapCount =0;
};
